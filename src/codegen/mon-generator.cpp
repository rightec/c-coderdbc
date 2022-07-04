#include "mon-generator.h"
#include "helpers/formatter.h"

uint32_t MonGenerator::FillHeader(FileWriter& wr, std::vector<CiExpr_t*>& sigs,
  const std::string& name)
{
  wr.AppendLine(StrPrintLoc("#ifdef %s_USE_MONO_FMON", str_toupper(name).c_str()));
  wr.AppendLine();

  wr.AppendLine(StrPrintLoc("void _FMon_MONO_%s(FrameMonitor_t* _mon, uint32_t msgid);", name.c_str()));
  wr.AppendLine();

  for (auto it = sigs.begin(); it != sigs.end(); ++it)
  {

    auto msg = &((*it)->msg);
    wr.AppendLine(StrPrintLoc("#define FMon_%s_%s(x, y) _FMon_MONO_%s((x), (y))", msg->Name.c_str(), name.c_str(),
        name.c_str()));
  }

  wr.AppendLine();
  wr.AppendLine("#else");
  wr.AppendLine();

  for (auto it = sigs.begin(); it != sigs.end(); ++it)
  {
    auto msg = &((*it)->msg);
    wr.AppendLine(StrPrintLoc("void _FMon_%s_%s(FrameMonitor_t* _mon, uint32_t msgid);",
        msg->Name.c_str(), name.c_str()));
  }

  wr.AppendLine();

  for (auto it = sigs.begin(); it != sigs.end(); ++it)
  {
    auto msg = &((*it)->msg);
    wr.AppendLine(StrPrintLoc("#define FMon_%s_%s(x, y) _FMon_%s_%s((x), (y))",
        msg->Name.c_str(), name.c_str(),
        msg->Name.c_str(), name.c_str()));
  }

  wr.AppendLine();
  wr.AppendLine("#endif");
  wr.AppendLine();

  return 0;
}

uint32_t MonGenerator::FillSource(FileWriter& wr, std::vector<CiExpr_t*>& sigs, const std::string& name)
{
  wr.AppendLine(StrPrintLoc("#ifdef %s_USE_MONO_FMON", str_toupper(name).c_str()));
  wr.AppendLine();
  wr.AppendLine(StrPrintLoc("void _FMon_MONO_%s(FrameMonitor_t* _mon, uint32_t msgid)", name.c_str()));
  wr.AppendLine("{");
  wr.AppendLine("  (void)_mon;");
  wr.AppendLine("  (void)msgid;");
  wr.AppendLine("}");
  wr.AppendLine();
  wr.AppendLine("#else");
  wr.AppendLine();

  for (auto it = sigs.begin(); it != sigs.end(); ++it)
  {
    auto msg = &((*it)->msg);
    wr.AppendLine(
      StrPrintLoc("void _FMon_%s_%s(FrameMonitor_t* _mon, uint32_t msgid)\n{\n  (void)_mon;\n  (void)msgid;\n}\n",
        msg->Name.c_str(), name.c_str()));
  }

  wr.AppendLine(StrPrintLoc("#endif // %s_USE_MONO_FMON", str_toupper(name).c_str()));
  wr.AppendLine();

  return 0;
}

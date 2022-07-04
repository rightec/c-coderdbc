#pragma once

#include <stdint.h>
#include "filewriter.h"
#include "c-sigprinter.h"

class MonGenerator {
 public:

  MonGenerator() = default;

  uint32_t FillHeader(FileWriter& wr, std::vector<CiExpr_t*>& sigs, const std::string& name);
  uint32_t FillSource(FileWriter& wr, std::vector<CiExpr_t*>& sigs, const std::string& name);
};

#include <iostream>
#include <fstream>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include "filewriter.h"

template<size_t N = 4096>
std::string __print_loc__(const char* format, va_list args)
{
  // TODO: make N sanitizing here to prevent memory errors
  char work_buff[N] = {0};
  auto ret = vsnprintf(work_buff, N, format, args);

  assert(ret < N);
  // make string from local array
  return work_buff;
}

FileWriter::FileWriter()
{
}

FileWriter::~FileWriter()
{
}

void FileWriter::Flush()
{
  strm.clear();
}

void FileWriter::Flush(const std::string& fpath)
{
  std::ofstream wfile;

  wfile.open(fpath, std::ios::out);

  wfile << strm.rdbuf();

  wfile.close();

  Flush();
}

int32_t FileWriter::Append(const char* frmt, ...)
{
  va_list args;
  va_start(args, frmt);

  auto ret = __print_loc__(frmt, args);

  va_end(args);

  // make string from local array
  AppendText(ret);
  AppendText("\n");
  return ret.size() + 1;
}

void FileWriter::AppendLine(uint32_t empty_lines)
{
  while (empty_lines--)
  {
    AppendText("\n");
  }
}

void FileWriter::AppendText(const char* text)
{
  std::string str = text;
  AppendText(str);
}

void FileWriter::AppendLine(const char* text, uint32_t post_empty_lines)
{
  AppendText(text);
  AppendLine(post_empty_lines);
}


void FileWriter::AppendText(const std::string& str)
{
  strm << str;
}

void FileWriter::AppendLine(const std::string& str)
{
  AppendText(str);
  AppendText("\n");
}


#pragma once

#include <stdint.h>

#include <string>
#include <sstream>

class FileWriter {
 public:

  FileWriter();
  ~FileWriter();

  void Flush();
  void Flush(const std::string& filename);

  void AppendText(const char* text);
  void AppendLine(const char* text, uint32_t post_empty_lines = 1);

  void AppendText(const std::string& str);
  void AppendLine(const std::string& str);

  void AppendLine(uint32_t empty_lines = 1);

 private:

  std::stringstream strm;

};

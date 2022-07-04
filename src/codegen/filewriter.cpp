#include <iostream>
#include <fstream>
#include "filewriter.h"


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


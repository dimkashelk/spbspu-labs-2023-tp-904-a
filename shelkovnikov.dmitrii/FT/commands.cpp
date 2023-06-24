#include "commands.h"
#include <fstream>
#include <vector>
#include <algorithm>
namespace
{
  char toLower(char c)
  {
    return static_cast< char >(std::tolower(c));
  }
  std::string toLowerString(const std::string &str)
  {
    std::string newStr;
    std::transform(str.begin(), str.end(), newStr.begin(), toLower);
  }
}
void dimkashelk::load(text_dict &dict, c_str filename)
{
  std::ifstream ifs(filename.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
  if (!ifs)
  {
    throw std::runtime_error("Can't open file");
  }
  std::ifstream::pos_type fileSize = ifs.tellg();
  ifs.seekg(0, std::ios::beg);
  std::vector< char > bytes(fileSize);
  ifs.read(bytes.data(), fileSize);
  dict[filename] = std::string(bytes.data(), fileSize);
}
void dimkashelk::analyze(frequency_dict &dict, text_dict &text, c_str filename)
{
  if (dict.find(filename) == dict.end())
  {
    load(text, filename);
  }
  
}

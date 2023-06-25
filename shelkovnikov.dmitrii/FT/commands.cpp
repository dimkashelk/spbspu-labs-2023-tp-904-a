#include "commands.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "parser.h"
#include "io.h"
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
    return newStr;
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
  Parser parser(text[filename]);
  auto &dict_text = dict[filename];
  while (parser.hasNext())
  {
    ++dict_text[toLowerString(parser())];
  }
}
void dimkashelk::exportToFile(frequency_dict &dict, c_str dictname, c_str filename)
{
  std::ofstream out(filename);
  if (!out)
  {
    throw std::runtime_error("Can't open file");
  }
  using pairIter = std::ostream_iterator< MapPair >;
  auto &data = dict.at(dictname);
  std::copy(data.begin(), data.end(), pairIter(out, "\n"));
}

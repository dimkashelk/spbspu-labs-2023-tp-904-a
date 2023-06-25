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
  std::ostream &outTwoEmptyLines(std::ostream &out)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    return out << "\n\n";
  }
  std::string toLowerString(const std::string &str)
  {
    std::string newStr;
    std::transform(str.begin(), str.end(), newStr.begin(), toLower);
    return newStr;
  }
  std::ostream &exportText(std::ostream &out, text_dict &dict, std::string filename)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    return out << dict.at(filename);
  }
  std::ostream &exportFreqDict(std::ostream &out, frequency_dict &dict, const std::string &filename)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    using pairIter = std::ostream_iterator< dimkashelk::MapPair >;
    auto &data = dict.at(filename);
    std::copy(data.begin(), data.end(), pairIter(out, "\n"));
    return out;
  }
}
void dimkashelk::load(all_data &dict, c_s filename)
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
  dict.second[filename] = std::string(bytes.data(), fileSize);
}
void dimkashelk::analyze(all_data &dict, c_s filename)
{
  if (dict.first.find(filename) == dict.first.end())
  {
    load(dict, filename);
  }
  Parser parser(dict.second[filename]);
  auto &dict_text = dict.first[filename];
  while (parser.hasNext())
  {
    ++dict_text[toLowerString(parser())];
  }
}
void dimkashelk::exportToFile(all_data &dict, c_s dictname, c_s filename)
{
  std::ofstream out(filename);
  if (!out)
  {
    throw std::runtime_error("Can't open file");
  }
  exportFreqDict(out, dict.first, dictname);
}
void dimkashelk::exportWithText(frequency_dict &dict, text_dict &dictText, c_s dictname, c_s filename)
{
  std::ofstream out(filename);
  if (!out)
  {
    throw std::runtime_error("Can't open file");
  }
  exportText(out, dictText, dictname) << outTwoEmptyLines;
  exportFreqDict(out, dict, dictname);
}
void dimkashelk::printWord(frequency_dict &dict, c_s dictname, c_s word, std::ostream &out)
{

}

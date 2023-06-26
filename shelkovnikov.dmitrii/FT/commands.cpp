#include "commands.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
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
  std::ostream &outEmptyDictMessage(std::ostream &out)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    return out << "<EMPTY>";
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
    if (data.size() == 0)
    {
      return outEmptyDictMessage(out) << "\n";
    }
    std::copy(data.begin(), data.end(), pairIter(out, "\n"));
    return out;
  }
  bool isGreaterCount(const std::pair< const std::string, size_t > &pair, size_t count)
  {
    return pair.second >= count;
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
void dimkashelk::exportWithText(all_data &dict, c_s dictname, c_s filename)
{
  std::ofstream out(filename);
  if (!out)
  {
    throw std::runtime_error("Can't open file");
  }
  exportText(out, dict.second, dictname) << outTwoEmptyLines;
  exportFreqDict(out, dict.first, dictname);
}
std::ostream &dimkashelk::printWord(all_data &dict, c_s dictname, c_s word, std::ostream &out)
{
  return out << dict.first.at(dictname).at(word);
}
std::ostream &dimkashelk::print(all_data &dict, c_s filename, std::ostream &out)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  return exportFreqDict(out, dict.first, filename);
}
void dimkashelk::deleteWord(all_data &dict, c_s dictname, c_s word)
{
  dict.first.at(dictname).erase(word);
}
void dimkashelk::deleteDict(all_data &dict, c_s filename)
{
  dict.first.erase(filename);
}
void dimkashelk::remove(all_data &dict, c_s filename)
{
  dict.second.erase(filename);
}
void dimkashelk::getTop(all_data &dict, c_s dictname, size_t count, std::ostream &out)
{
  using namespace std::placeholders;
  auto func = std::bind(isGreaterCount, _1, count);
  std::vector< MapPair > data;
  std::copy_if(dict.first[dictname].begin(), dict.first[dictname].end(), std::back_inserter(data), func);
  std::sort(data.begin(), data.end());
  std::reverse(data.begin(), data.end());
  using pairIter = std::ostream_iterator< dimkashelk::MapPair >;
  std::copy(data.begin(), data.end(), pairIter(out, "\n"));
}
void dimkashelk::getComplement(all_data &dict, c_s newdata, c_s dict1, c_s dict2)
{
  dict.first[newdata] = dict.first[dict1];
  for (auto &item: dict.first[dict2])
  {
    auto res = dict.first[newdata].find(item.first);
    if (res == dict.first[newdata].end())
    {
      continue;
    }
    if (res->second >= item.second)
    {
      dict.first[newdata].erase(res);
    }
    else
    {
      res->second -= item.second;
    }
  }
}
void dimkashelk::getIntersect(all_data &dict, c_s newdata, c_s dict1, c_s dict2)
{
  dict.first[newdata] = dict.first[dict1];
  for (auto &item: dict.first[dict2])
  {
    auto res = dict.first[newdata].find(item.first);
    if (res == dict.first[newdata].end())
    {
      continue;
    }
    res->second = std::min(res->second, item.second);
  }
}

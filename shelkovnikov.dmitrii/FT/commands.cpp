#include "commands.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include "parser.h"
#include "mappair.h"
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
  bool isGreaterCount(const std::pair< const dimkashelk::Word, size_t > &pair, size_t count)
  {
    return pair.second >= count;
  }
  std::ostream &outInfoAboutLoadCommand(std::ostream &out)
  {
    return out << "load <dictname> <filename> - loads text from a file and stores it "
                  "in the dictionary <dictname> with the <filename> key";
  }
  std::ostream &outInfoAboutAnalyzeCommand(std::ostream &out)
  {
    return out << "analyze <dictname> <filename> - analyzes text from a file stored in "
                  "memory, if the file is not saved, then opens and saves the text, and "
                  "then analyzes, saves the result in the dictionary <dictname> with the "
                  "key <filename>";
  }
  std::ostream &outInfoAboutExportToFileCommand(std::ostream &out)
  {
    return out << "export <dictname> <output filename> - exports frequency dictionary "
                  "data for a specific file in <output filename>";
  }
  std::ostream &outInfoAboutExportWithTextCommand(std::ostream &out)
  {
    return out << "exportWithText <dictname> <output filename> - exports text and "
                  "frequency dictionary data to <output filename>";
  }
  std::ostream &outInfoAboutPrintWordCommand(std::ostream &out)
  {
    return out << "printWord <dictname> <word> - outputs the number of times the word was used in the text";
  }
  std::ostream &outInfoAboutPrintCommand(std::ostream &out)
  {
    return out << "print <dictname> - outputs a frequency analysis dictionary";
  }
  std::ostream &outInfoAboutDeleteWordCommand(std::ostream &out)
  {
    return out << "deleteWord <dictname> <word> - deletes a word from the dictionary";
  }
  std::ostream &outInfoAboutDeleteDictCommand(std::ostream &out)
  {
    return out << "delete <dictname> - deletes the frequency dictionary";
  }
  std::ostream &outInfoAboutRemoveCommand(std::ostream &out)
  {
    return out << "remove <dictname> - deletes the downloaded text";
  }
  std::ostream &outInfoAboutGetTopCommand(std::ostream &out)
  {
    return out << "top <dictname> <count> - outputs <count> of the most common words";
  }
  std::ostream &outInfoAboutGetComplementCommand(std::ostream &out)
  {
    return out << "complement <newdataset> <dictname-1> <dictname-2> - builds a dictionary "
                  "with a new name as a subtraction of the sets of two other dictionaries";
  }
  std::ostream &outInfoAboutGetIntersectCommand(std::ostream &out)
  {
    return out << "intersect <newdataset> <dictname-1> <dictname-2> - builds a dictionary "
                  "with a new name as the intersection of sets of two other dictionaries";
  }
  std::ostream &outInfoAboutGetUnionCommand(std::ostream &out)
  {
    return out << "union <newdataset> <dictname-1> <dictname-2> - builds a dictionary "
                  "with a new name as a union of sets of two other dictionaries";
  }
  std::ostream &outInfoAboutHelpCommand(std::ostream &out)
  {
    return out << "help - displays a list of available commands";
  }
  std::string inputString(std::istream &in_)
  {
    std::istream::sentry sentry(in_);
    std::string res;
    if (sentry)
    {
      in_ >> res;
      return res;
    }
    else
    {
      throw std::logic_error("Cannot input");
    }
  }
  std::pair< std::string, std::string > input2String(std::istream &in_)
  {
    return {inputString(in_), inputString(in_)};
  }
  std::tuple< std::string, std::string, std::string > input3String(std::istream &in_)
  {
    return std::tuple< std::string, std::string, std::string >(inputString(in_), inputString(in_), inputString(in_));
  }
  size_t inputSizeT(std::istream &in_)
  {
    std::istream::sentry sentry(in_);
    size_t res;
    if (sentry)
    {
      in_ >> res;
      return res;
    }
    else
    {
      throw std::logic_error("Cannot input");
    }
  }
}
void load(all_data &dict, c_s filename)
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
void analyze(all_data &dict, c_s filename)
{
  if (dict.first.find(filename) == dict.first.end())
  {
    load(dict, filename);
  }
  Parser parser(dict.second[filename]);
  auto &dict_text = dict.first[filename];
  while (parser.hasNext())
  {
    dimkashelk::Word w(parser());
    ++dict_text[w];
  }
}
void exportToFile(all_data &dict, c_s dictname, c_s filename)
{
  std::ofstream out(filename);
  if (!out)
  {
    throw std::runtime_error("Can't open file");
  }
  exportFreqDict(out, dict.first, dictname);
}
void exportWithText(all_data &dict, c_s dictname, c_s filename)
{
  std::ofstream out(filename);
  if (!out)
  {
    throw std::runtime_error("Can't open file");
  }
  exportText(out, dict.second, dictname) << outTwoEmptyLines;
  exportFreqDict(out, dict.first, dictname);
}
void printWord(all_data &dict, c_s dictname, c_s word, std::ostream &out)
{
  dimkashelk::Word w(word);
  out << dict.first.at(dictname).at(w) << "\n";
}
void print(all_data &dict, c_s filename, std::ostream &out)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return;
  }
  exportFreqDict(out, dict.first, filename) << "\n";
}
void deleteWord(all_data &dict, c_s dictname, c_s word)
{
  dimkashelk::Word w(word);
  dict.first.at(dictname).erase(w);
}
void deleteDict(all_data &dict, c_s filename)
{
  dict.first.erase(filename);
}
void remove(all_data &dict, c_s filename)
{
  dict.second.erase(filename);
}
void getTop(all_data &dict, c_s dictname, size_t count, std::ostream &out)
{
  using namespace std::placeholders;
  auto func = std::bind(isGreaterCount, _1, count);
  std::vector< dimkashelk::MapPair > data;
  std::copy_if(dict.first[dictname].begin(), dict.first[dictname].end(), std::back_inserter(data), func);
  std::sort(data.begin(), data.end());
  std::reverse(data.begin(), data.end());
  using pairIter = std::ostream_iterator< dimkashelk::MapPair >;
  std::copy(data.begin(), data.end(), pairIter(out, "\n"));
}
void getComplement(all_data &dict, c_s newdata, c_s dict1, c_s dict2)
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
void getIntersect(all_data &dict, c_s newdata, c_s dict1, c_s dict2)
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
void getUnion(all_data &dict, c_s newdata, c_s dict1, c_s dict2)
{
  dict.first[newdata] = dict.first[dict1];
  for (auto &item: dict.first[dict2])
  {
    auto res = dict.first[newdata].find(item.first);
    if (res == dict.first[newdata].end())
    {
      dict.first[newdata][item.first] = item.second;
    }
    else
    {
      res->second += item.second;
    }
  }
}
void help(std::ostream &out)
{
  outInfoAboutLoadCommand(out) << "\n";
  outInfoAboutAnalyzeCommand(out) << "\n";
  outInfoAboutExportToFileCommand(out) << "\n";
  outInfoAboutExportWithTextCommand(out) << "\n";
  outInfoAboutPrintWordCommand(out) << "\n";
  outInfoAboutPrintCommand(out) << "\n";
  outInfoAboutDeleteWordCommand(out) << "\n";
  outInfoAboutDeleteDictCommand(out) << "\n";
  outInfoAboutRemoveCommand(out) << "\n";
  outInfoAboutGetTopCommand(out) << "\n";
  outInfoAboutGetComplementCommand(out) << "\n";
  outInfoAboutGetIntersectCommand(out) << "\n";
  outInfoAboutGetUnionCommand(out) << "\n";
  outInfoAboutHelpCommand(out) << "\n";
}

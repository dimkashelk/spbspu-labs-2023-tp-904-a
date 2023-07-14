#ifndef FT_COMMANDS_H
#define FT_COMMANDS_H
#include <map>
#include <string>
#include <ostream>
#include "word.h"
using frequency_dict = std::map< std::string, std::map< dimkashelk::Word, size_t > >;
using text_dict = std::map< std::string, std::string >;
using all_data = std::pair< frequency_dict, text_dict >;
using c_s = const std::string &;
void load(all_data &dict, std::istream &in);
void analyze(all_data &dict, std::istream &in);
void exportToFile(all_data &dict, std::istream &in);
void exportWithText(all_data &dict, std::istream &in);
void printWord(all_data &dict, std::istream &in, std::ostream &out);
void print(all_data &dict, std::istream &in, std::ostream &out);
void deleteWord(all_data &dict, std::istream &in);
void deleteDict(all_data &dict, std::istream &in);
void remove(all_data &dict, std::istream &in);
void getTop(all_data &dict, std::istream &in, std::ostream &out);
void getComplement(all_data &dict, std::istream &in);
void getIntersect(all_data &dict, std::istream &in);
void getUnion(all_data &dict, std::istream &in);
void help(std::ostream &out);
#endif

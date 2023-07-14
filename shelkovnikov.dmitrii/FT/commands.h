#ifndef FT_COMMANDS_H
#define FT_COMMANDS_H
#include <map>
#include <string>
#include <ostream>
#include "word.h"
using frequency_dict = std::map< std::string, std::map< dimkashelk::Word, size_t > >;
using dict_with_text = std::map< std::string, std::string >;
using frequency_text_pair = std::pair< frequency_dict, dict_with_text >;
void load(frequency_text_pair &dict, std::istream &in);
void analyze(frequency_text_pair &dict, std::istream &in);
void exportToFile(frequency_text_pair &dict, std::istream &in);
void exportWithText(frequency_text_pair &dict, std::istream &in);
void printWord(frequency_text_pair &dict, std::istream &in, std::ostream &out);
void print(frequency_text_pair &dict, std::istream &in, std::ostream &out);
void deleteWord(frequency_text_pair &dict, std::istream &in);
void deleteDict(frequency_text_pair &dict, std::istream &in);
void remove(frequency_text_pair &dict, std::istream &in);
void getTop(frequency_text_pair &dict, std::istream &in, std::ostream &out);
void getComplement(frequency_text_pair &dict, std::istream &in);
void getIntersect(frequency_text_pair &dict, std::istream &in);
void getUnion(frequency_text_pair &dict, std::istream &in);
void help(std::ostream &out);
#endif

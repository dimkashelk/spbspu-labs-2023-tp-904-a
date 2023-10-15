#include "commands.h"
#include <forward_list>
#include <fstream>

std::string cutS(std::string& line)
{
  std::string res = "";
  std::size_t pos = line.find(' ');

  if (pos != std::string::npos)
  {
    res = line.substr(0, pos);
    line.erase(0, pos + 1);

    return res;
  }
  else if (line != "")
  {
    res = line;
    line = "";

    return res;
  }
  else
  {
    throw std::invalid_argument("incorrect args");
  }
}

void dmitriev::addBook(library& lib, std::istream& inp)
{
  std::string line = "";
  std::getline(inp, line);

  std::string dirName = cutS(line);

  Book newBook{cutS(line), cutS(line), cutS(line), cutS(line), std::stol(cutS(line))};
  if (lib.at(dirName).find(newBook.key) != lib.at(dirName).end())
  {
    throw std::invalid_argument("book alrady exist");
  }
  lib.at(dirName)[newBook.key] = newBook;
}

size_t hammingDistance(const std::string& lhs, const std::string& rhs)
{
  size_t distance = 0;
  size_t length = std::min(lhs.length(), rhs.length());

  for (size_t i = 0; i < length; i++)
  {
    if (lhs[i] != rhs[i])
    {
      distance++;
    }
  }

  distance += std::abs(static_cast< int >(lhs.length() - rhs.length()));

  return distance;
}

std::forward_list< dmitriev::Book > findBooks(const dmitriev::library& lib,
  const std::string& dir,
  const std::string& query,
  const std::string& parameter,
  size_t k)
{
  std::forward_list< dmitriev::Book > result;
  const dmitriev::directory& books = lib.at(dir);

  typename dmitriev::directory::const_iterator it = books.cbegin();
  for (; it != books.cend(); it++)
  {
    bool p1 = (parameter == "year" && std::to_string(it->second.year) == query);
    bool p2 = (parameter == "isbn" && it->second.isbn == query);

    std::string rhsStr = parameter == "title" ? it->second.title : it->second.author;
    size_t distance = hammingDistance(query, rhsStr);
    bool p3 = (parameter == "title" || parameter == "author") && distance <= k;

    if (p1 || p2 || p3)
    {
      result.push_front(it->second);
    }
  }

  return result;
}

void dmitriev::deleteBook(library& lib, std::istream& inp)
{
  std::string line = "";
  std::getline(inp, line);

  std::string dirName = cutS(line);
  std::string query = cutS(line);
  std::string parameter = cutS(line);

  std::forward_list< Book > result = findBooks(lib, dirName, query, parameter, 0);
  if (!result.empty())
  {
    lib.at(dirName).erase(result.front().key);
  }
}

void dmitriev::copyBook(library& lib, std::istream& inp)
{
  std::string line = "";
  std::getline(inp, line);

  std::string dirFrom = cutS(line);
  std::string dirTo = cutS(line);
  std::string query = cutS(line);
  std::string parameter = cutS(line);

  std::forward_list< Book > result = findBooks(lib, dirFrom, query, parameter, 0);
  if (!result.empty())
  {
    Book newBook = result.front();
    if (lib.at(dirTo).find(newBook.key) != lib.at(dirTo).end())
    {
      throw std::invalid_argument("book alrady exist");
    }
    lib.at(dirTo)[newBook.key] = newBook;
  }
}

void dmitriev::createDirection(library& lib, std::istream& inp)
{
  std::string line = "";
  std::getline(inp, line);

  std::string dirName = cutS(line);
  if (lib.find(dirName) != lib.end())
  {
    throw std::invalid_argument("dir alrady exist");
  }
  lib[dirName];
}

void dmitriev::deleteDirection(library& lib, std::istream& inp)
{
  std::string line = "";
  std::getline(inp, line);

  std::string dirName = cutS(line);
  if (lib.find(dirName) == lib.end())
  {
    throw std::invalid_argument("dir alrady exist");
  }

  lib.erase(dirName);
}

void dmitriev::combineDirections(library& lib, std::istream& inp)
{
  std::string line = "";
  std::getline(inp, line);

  std::string newDirName = cutS(line);//
  std::string lhsDirName = cutS(line);
  std::string rhsDirName = cutS(line);

  directory newDir = lib.at(lhsDirName);

  typename directory::iterator it = lib.at(rhsDirName).begin();
  for (; it != lib.at(rhsDirName).end(); it++)
  {
    if (lib.at(lhsDirName).find(it->first) == lib.at(lhsDirName).end())
    {
      newDir.insert(*it);
    }
  }

  if (lib.find(newDirName) != lib.end())
  {
    throw std::invalid_argument("dir alrady exist");
  }
  lib[newDirName] = newDir;
}

void dmitriev::downloadDirection(library& lib, std::istream& inp)
{
  std::string line = "";
  std::getline(inp, line);

  std::string dirName = cutS(line);
  std::string fileName = cutS(line);

  std::ifstream file(fileName);
  if (!file.is_open())
  {
    throw std::invalid_argument("incorrect file name");
  }

  directory newDir;
  Book newBook;
  while (!file.eof())
  {
    file >> newBook;
    newDir[newBook.key] = newBook;
  }

  if (lib.find(dirName) != lib.end())
  {
    throw std::invalid_argument("dir alrady exist");
  }
  lib[dirName] = newDir;
}

void printBook(const dmitriev::Book& book, std::ostream& out)
{
  out << "key: " << book.key << '\n';
  out << "title: " << book.title << '\n';
  out << "author: " << book.author << '\n';
  out << "isbn: " << book.isbn << '\n';
  out << "year: " << book.year;
}

void dmitriev::printFindedBooks(const library& lib, std::ostream& out, std::istream& inp)
{
  std::string line;
  std::getline(inp, line);

  std::forward_list< Book > result;
  std::string dirName = cutS(line);
  std::string query = cutS(line);
  std::string parameter = cutS(line);
  result = findBooks(lib, dirName, query, parameter, std::stol(cutS(line)));

  typename std::forward_list< Book >::const_iterator it = result.cbegin();
  if (it == result.cend())
  {
    out << "<EMPTY>";//
    return;
  }
  printBook(*it++, out);
  while (it != result.cend())
  {
    out << "\n\n";
    printBook(*it++, out);
  }
}

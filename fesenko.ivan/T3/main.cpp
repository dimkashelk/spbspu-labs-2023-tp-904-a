#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Invalid number of arguments\n";
    return 2;
  }
  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "Can`t open the file\n";
    return 2;
  }
}

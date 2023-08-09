#include <iostream>
#include <limits>
#include "auxiliary_fns.hpp"
#include "dict.hpp"
int main()
{
  litvin::command_dict_t commands;
  litvin::dicts_list_t list_of_dicts;
  litvin::command_descriptors cmd_descriptors = litvin::createCommandDescriptorsDict();
  while (!std::cin.eof())
  {
    try
    {
      std::string command = " ";
      command = litvin::inputCommand(std::cin);
      litvin::runCommand(commands, list_of_dicts, cmd_descriptors, command, std::cout, std::cin);
    } catch (const std::runtime_error & error)
    {
      break;
    }
    catch (const std::logic_error & error)
    {
      std::cout << "invalid command\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}

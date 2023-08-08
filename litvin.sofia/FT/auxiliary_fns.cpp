#include "auxiliary_fns.hpp"
litvin::command_dict_t::command_dict_t()
{
  dict1.insert({"SEARCH", searchWord});
  dict1.insert({"PRINT", printDict});
  dict1.insert({"DELETE", deleteDict});
  dict1.insert({"NEW", createNewDict});
  dict2.insert({"INSERT", insertWordTranslation});
  dict2.insert({"ADD", addWordTranslation});
  dict2.insert({"INTERSECT", intersectDictionaries});
  dict2.insert({"UNION", unionDictionaries});
  dict2.insert({"DIFFERENCE", subtractDictionaries});
  dict3.insert({"REMOVE", removeWordFromDict});
  dict3.insert({"PRINTL", printDictByLetter});
  dict4.insert({"EDIT", editWordTranslation});
  dict5.insert({"ERASE", eraseWordTranslation});
}

#include <vector>
#include <string>

#if !defined(MENU_HPP)
#define MENU_HPP

int menu(const char *title, std::vector<std::string> items);

bool confirmation_message(const char *title, const char *question);
#endif
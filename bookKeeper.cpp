#include "Headers/Charge.h"
#include "Headers/Material.h"
#include "Headers/Patron.h"
#include "Headers/Address.h"
#include "Headers/Menu.h"
#include <iostream>
#include <stdlib.h>

int main() {
  Menu * menu = new Menu;

  std::cout << "\n\n|===================================|\n\n" << std::endl;

  menu->mainMenu();

  delete menu;

  return 0;
}

#ifndef CHARGE_H
#define CHARGE_H
#include "Patron.h"
#include <ctime>
#include <stdlib.h>
#include <string>

class Charge {
  public:
    // Constructors
    Charge();
    Charge(Patron* borrowerIn);

    // Desctructor
    ~Charge();

    // Setters and getters
    Patron* getBorrower();

  private:

    Patron* borrower;

};
#endif

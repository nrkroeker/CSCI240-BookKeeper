#include "../Headers/Charge.h"

// Default constructor
Charge::Charge() {

}

// Other Constructor
Charge::Charge(Patron* borrowerIn) {
  this->borrower = borrowerIn;
}

// Destructor
Charge::~Charge() {
  // Delete errything
}

//======================================================================//

// Getters
Patron* Charge::getBorrower() {
  return this->borrower;
}

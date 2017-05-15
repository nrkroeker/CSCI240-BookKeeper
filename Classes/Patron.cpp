#include "../Headers/Patron.h"

// Default constructor
Patron::Patron() {
 // Create the thing.
}

// Other constructor
Patron::Patron(std::string firstNameIn, std::string lastNameIn, std::string emailIn, Address* addressIn, std::string cardNumberIn) {
  this->firstName = firstNameIn;
  this->lastName = lastNameIn;
  this->email = emailIn;
  this->address = addressIn;
  this->cardNumber = cardNumberIn;
}

// Destructor
Patron::~Patron() {
  // Here we delete.
}

//======================================================================//

// Getters
std::string Patron::getFirstName() {
  return this->firstName;
}

std::string Patron::getLastName() {
  return this->lastName;
}

std::string Patron::getEmail() {
  return this->email;
}

Address* Patron::getAddress() {
  return this->address;
}

std::string Patron::getCardNumber() {
  return this->cardNumber;
}

// Setters
void Patron::setFirstName(std::string newFirstName) {
  this->firstName = newFirstName;
}

void Patron::setLastName(std::string newLastName) {
  this->lastName = newLastName;
}

void Patron::setEmail(std::string newEmail) {
  this->email = newEmail;
}

void Patron::setAddress(Address* newAddress) {
  this->address = newAddress;
}

void Patron::setCardNumber(std::string newCard) {
  this->cardNumber = newCard;
}

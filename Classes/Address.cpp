#include "../Headers/Address.h"
#include <stdlib.h>

// Default constructor
Address::Address() {

}

// Other constructor
Address::Address(std::string streetIn, std::string cityIn, std::string stateIn, std::string zipCodeIn) {
  this->street = streetIn;
  this->city = cityIn;
  this->state = stateIn;
  this->zipCode = zipCodeIn;
}

// Destructor
Address::~Address() {
    // Deleting everything here xD
}

//======================================================================//

// Getters
std::string Address::getStreet() {
  return this->street;
}

std::string Address::getCity() {
  return this->city;
}

std::string Address::getState() {
  return this->state;
}

std::string Address::getZipcode() {
  return this->zipCode;
}

// Setters

void Address::setStreet(std::string newStreet) {
  this->street = newStreet;
}

void Address::setCity(std::string newCity) {
  this->city = newCity;
}

void Address::setState(std::string newState) {
  this->state = newState;
}

void Address::setZipcode(std::string newZipCode) {
  this->zipCode = newZipCode;
}

#include "../Headers/Material.h"

// Default constructor
Material::Material() {

}

// Other constructor
Material::Material(std::string materialIdIn, std::string titleIn, std::string typeIn, std::string creatorIn, std::string creatorTypeIn, std::string locationIn) {
  this->materialId = materialIdIn;
  this->title = titleIn;
  this->type = typeIn;
  this->creator = creatorIn;
  this->creatorType = creatorTypeIn;
  this->location = locationIn;
}

// Destructor
Material::~Material() {
  // Delete the whole darn thing
}

//======================================================================//

// Getters
std::string Material::getId() {
  return this->materialId;
}

std::string Material::getTitle() {
  return this->title;
}

std::string Material::getType() {
  return this->type;
}

std::string Material::getCreator() {
  return this->creator;
}

std::string Material::getCreatorType() {
  return this->creatorType;
}

std::string Material::getLocation() {
  return this->location;
}

Charge* Material::getCurrentCharge() {
  return this->currentCharge;
}

// Setters

void Material::setId(std::string newId) {
  this->materialId = newId;
}

void Material::setLocation(std::string newLocation) {
  this->location = newLocation;
}

// Alter material charges
void Material::checkIn(Charge* newCharge) {
  this->currentCharge = newCharge;
}

void Material::checkOut(Patron* newBorrower) {


}

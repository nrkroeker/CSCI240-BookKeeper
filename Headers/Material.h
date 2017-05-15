#ifndef MATERIAL_H
#define MATERIAL_H
#include "Patron.h"
#include "Charge.h"
#include <stdlib.h>
#include <string>

class Material {
  public:
    // Constructors
    Material();
    Material(std::string materialIdIn, std::string titleIn, std::string typeIn, std::string creatorIn, std::string creatorTypeIn, std::string locationIn);

    // Destructor
    ~Material();

    // Getters
    std::string getId();
    std::string getTitle();
    std::string getType();
    std::string getCreator();
    std::string getCreatorType();
    std::string getDateCreated();
    std::string getLocation();
    Charge* getCurrentCharge();
    Charge* getLastCharge();

    // // Gets information from the Charge attached
    // Patron getBorrower();
    // Patron getLastBorrower();

    // Setters
    void setId(std::string newId);
    void setLocation(std::string newLocation);

    // Sets current and previous charges
    void checkIn(Charge* newCharge); // Move currentCharge to lastCharge and set currentCharge to a new Charge with null borrower
    void checkOut(Patron* newBorrower);

  private:
    std::string materialId; // Restrict to 10 digits
    std::string title;
    std::string type;
    std::string creator;
    std::string creatorType; // Check with array of possible creator types
    std::string location; // Check with array of possible locations

    // Charge object attached to it has current and last borrower information
    Charge* currentCharge;
    
};
#endif

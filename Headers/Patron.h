#ifndef PATRON_H
#define PATRON_H
#include "Address.h"
#include <stdlib.h>
#include <string>

class Patron {
  public:
    // Constructors
    Patron();
    Patron(std::string firstNameIn, std::string lastNameIn, std::string emailIn, Address* addressIn, std::string cardNumberIn);

    // Destructor
    ~Patron();

    // Getters
    std::string getFirstName();
    std::string getLastName();
    std::string getEmail();
    Address* getAddress();
    std::string getCardNumber();

    // Setters
    void setFirstName(std::string newFirstName);
    void setLastName(std::string newLastName);
    void setEmail(std::string newEmail);
    void setAddress(Address* newAddress); // Create Address object first
    void setCardNumber(std::string newCard);


  private:
    std::string firstName;
    std::string lastName;
    std::string email; // Must include @ and end with .-something
    Address *address;

    std::string cardNumber; // Restrict to 10 digits, starting with 2146

};
#endif

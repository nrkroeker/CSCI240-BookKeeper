#ifndef ADDRESS_H
#define ADDRESS_H
#include <stdlib.h>
#include <string>

class Address {
  public:
    // Constructors
    Address();
    Address(std::string streetIn, std::string cityIn, std::string stateIn, std::string zipCodeIn);

    // Desctructor
    ~Address();

    // Getters
    std::string getStreet();
    std::string getCity();
    std::string getState();
    std::string getZipcode();

    // Setters
    void setStreet(std::string newStreet);
    void setCity(std::string newCity);
    void setState(std::string newState);
    void setZipcode(std::string newZipCode);

  private:
    std::string street;
    std::string city;
    std::string state; // Restrict to 2 characters
    std::string zipCode; // Restrict to 5 digits

};
#endif

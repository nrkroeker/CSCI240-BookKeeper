#ifndef MENU_H
#define MENU_H
#include <stdlib.h>
#include <string>
#include "Material.h"
#include "Patron.h"

#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>


class Menu {
  public:
    // Constructor
    Menu();

    // Destructor
    ~Menu();

    void mainMenu();

  private:

    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;

    std::string menuInput;

    // Patron inputs
    std::string firstNameInput;
    std::string lastNameInput;
    std::string emailInput;
    std::string cardInput;
    std::string streetInput;
    std::string cityInput;
    std::string stateInput;
    std::string zipInput;
    std::string deleteInput;

    // Material inputs
    std::string materialIdInput;
    std::string titleInput;
    std::string typeInput;
    std::string creatorInput;
    std::string creatorTypeInput;
    std::string locationInput;

    // Variables for SQL returned IDs
    std::string addressId;
    std::string patronId;
    std::string materialId;
    std::string chargeId;

    // Most recent objects interacted with
    Address* activeAddress;
    Patron* activePatron;
    Material* activeMaterial;
    Charge* activeCharge;

    // First menu options
    void patrons();
    void materials();
    void checkOut();
    void checkIn();

    // Patron menu options
    void addPatron();
    void searchPatron();
    void viewPatron();
    void editPatron();
    void deletePatron();

    // Material menu options
    void addMaterial();
    void searchMaterial();
    void viewMaterial();
    void deleteMaterial();

    void insertAddress();
    void insertPatron();
    void insertMaterial();
    
    void createPatronQuery();
    void createMaterialQuery();

    void updateAddress();
    void updatePatron();

    void invalid();
};
#endif

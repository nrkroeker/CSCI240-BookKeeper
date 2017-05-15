#include "../Headers/Menu.h"
#include "../Headers/Address.h"
#include "../Headers/Patron.h"
#include <iostream>
#include <stdlib.h>

#include <mysql_connection.h>
#include "mysql_driver.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>


Menu::Menu() {
}

Menu::~Menu() {

}

//=====================================================================//

void Menu::mainMenu() {

  this->driver = get_driver_instance();
  this->con = this->driver->connect("tcp://127.0.0.1:3306", "root", "H0n0rs240");

  this->stmt = this->con->createStatement();
  this->stmt->execute("USE library");

  bool keepGoing = true;
  std::cout << "Welcome to BookKeeper!\n\n" << std::endl;

  while(keepGoing) {
    std::cout << "|=========================|\n\nMain Menu\n\n1) Patrons \n2) Materials \n3) Check-out \n4) Check-in \n5) Exit\n\n" << std::endl;

    std::cout << "Please select an option > " << std::flush;
    std::cin >> this->menuInput;

    if (this->menuInput == "1") {
      this->patrons();
    } else if (this->menuInput == "2") {
      this->materials();
    } else if (this->menuInput == "3") {
      this->checkOut();
    } else if (this->menuInput == "4") {
      this->checkIn();
    } else if (this->menuInput == "5") {
      std::cout << "Now exiting...\n" << std::endl;
      keepGoing = false;
    } else {
      this->invalid();
    }

  }

  delete this->stmt;
  delete this->con;

}


//=====================================================================//

void Menu::patrons() {
  bool keepGoing = true;

  while(keepGoing) {
    std::cout << "|=========================|\n\nPatron Menu\n\n1) Add new patron \n2) Search for existing patron \n3) Return to main menu\n\n" << std::endl;
    std::cout << "Please select an option > " << std::flush;
    std::cin >> this->menuInput;

    if (this->menuInput == "1") {
      this->addPatron();
    } else if (this->menuInput == "2") {
      this->searchPatron();
    } else if (this->menuInput == "3") {
      keepGoing = false;
    } else {
      this->invalid();
    }
  }
}

//=====================================================================//

void Menu::materials() {
  bool keepGoing = true;
  while(keepGoing) {
  std::cout << "|=========================|\n\nMaterial Menu\n\n1) Add new material \n2) Search for existing material \n3) Return to main menu\n\n" << std::endl;

    std::cout << "Please select an option > " << std::flush;
    std::cin >> this->menuInput;

    if (menuInput == "1") {
      this->addMaterial();
    } else if (menuInput == "2") {
      this->searchMaterial();
    } else if (menuInput == "3") {
      keepGoing = false;
    } else {
      this->invalid();
    }
  }
}

//=====================================================================//

void Menu::checkOut() {
  std::cout << "|=========================|\n\nCheck-out\n\n" << std::endl;

  // Take in the card and item barcode numbers
  std::cout << "Card Number: " << std::flush;
  std::cin >> this->cardInput;

  std::cout << "Material ID: " << std::flush;
  std::cin >> this->materialIdInput;

  // Find the patron with the card number
  this->res = this->stmt->executeQuery("SELECT * FROM Patrons WHERE cardNumber = '" + this->cardInput + "'");

  while(this->res->next()) {
    this->patronId = this->res->getString("id");
  }

  this->createPatronQuery();

  this->stmt->execute("INSERT INTO Charges(borrower) VALUES ('" + this->patronId + "')");

  this->res = this->stmt->executeQuery("SELECT * FROM Charges WHERE borrower = '" + this->patronId + "'");

  while(this->res->next()) {
    this->chargeId = this->res->getString("id");
  }

  this->stmt->execute("UPDATE Materials SET current_charge = '" + this->chargeId + "', borrower = '" + this->patronId + "' WHERE material_id = '" + this->materialIdInput + "'");

  this->res = this->stmt->executeQuery("SELECT * FROM Materials WHERE material_id = '" + this->materialIdInput + "'");

  this->createMaterialQuery();

  std::cout << "\n" << this->activeMaterial->getTitle() << " has been successfully checked out." << std::endl;

}

//=====================================================================//

void Menu::checkIn() {
  std::cout << "|=========================|\n\nCheck-in Menu\n\n" << std::endl;

  std::cout << "Material ID: " << std::flush;
  std::cin >> this->materialIdInput;

  this->stmt->execute("UPDATE Materials SET current_charge = NULL, borrower = NULL WHERE material_id = '" + this->materialIdInput + "'");

  std::cout << "\nMaterial checked back in to library." << std::endl;
}

//=====================================================================//

// Patron menu methods

void Menu::addPatron() {

  std::cout << "|=========================|\n\nAdd a new patron\n" << std::endl;

  std::cout << "First Name: " << std::flush;
  std::cin >> this->firstNameInput;

  std::cout << "Last Name: " << std::flush;
  std::cin >> this->lastNameInput;

  std::cout << "Email: " << std::flush;
  std::cin >> this->emailInput;

  std::cout << "Card Number: " << std::flush;
  std::cin >> this->cardInput;

  std::cin.ignore();

  std::cout << "Street: " << std::flush;
  std::getline(std::cin, this->streetInput);

  std::cout << "City: " << std::flush;
  std::cin >> this->cityInput;

  std::cout << "State: " << std::flush;
  std::cin >> this->stateInput;

  std::cout << "Zipcode: " << std::flush;
  std::cin >> this->zipInput;

  this->activeAddress = new Address(this->streetInput, this->cityInput, this->stateInput, this->zipInput);

  this->insertAddress();

  this->activePatron = new Patron(this->firstNameInput, this->lastNameInput, this->emailInput, this->activeAddress, this->cardInput);

  this->insertPatron();

  this->viewPatron();

}

//=====================================================================//

void Menu::searchPatron() {
  bool keepGoing = true;
  while(keepGoing) {
    std::cout << "|=========================|\n\nSearch for existing patron \n\nSearch by: \n1) Name \n2) Card Number \n3) Back to patron menu\n" << std::endl;

    std::cout << "Please select an option > " << std::flush;
    std::cin >> this->menuInput;

    if (menuInput == "1") {
        std::cout << "First Name: " << std::flush;
        std::cin >> this->firstNameInput;

        std::cout << "Last Name: " << std::flush;
        std::cin >> this->lastNameInput;

        // ERROR HANDLING - need to check if Patron exists in database at all

        this->res = this->stmt->executeQuery("SELECT * FROM Patrons WHERE firstName = '" + this->firstNameInput + "' AND lastName = '" + this->lastNameInput + "'");

        this->createPatronQuery();

        delete this->res;
        this->viewPatron();
        keepGoing = false;

    } else if (menuInput == "2") {

      std::cout << "Card Number: " << std::flush;
      std::cin >> this->cardInput;

      this->res = this->stmt->executeQuery("SELECT * FROM Patrons WHERE cardNumber = '" + this->cardInput + "'");

      this->createPatronQuery();

      delete this->res;
      this->viewPatron();
      keepGoing = false;
    } else if (menuInput == "3") {
      keepGoing = false;
    } else {
      this->invalid();
    }
  }
}

//=====================================================================//

void Menu::viewPatron() {
  bool keepGoing = true;

  std::cout << "|=========================|\n\nView Patron\n" << std::endl;

  std::cout << "Name: " << this->activePatron->getFirstName() << " " << this->activePatron->getLastName() << std::endl;

  std::cout << "Email: " << this->activePatron->getEmail() << std::endl;

  std::cout << "Card Number: " << this->activePatron->getCardNumber() << std::endl;

  std::cout << "Address: " << this->activeAddress->getStreet() << " " << this->activeAddress->getCity() << ", " << this->activeAddress->getState() << " " << this->activeAddress->getZipcode() << std::endl;

  while(keepGoing) {
  std::cout << "\n\n1) Edit patron \n2) Delete patron \n3) Return to patron menu\n" << std::endl;

    std::cout << "Please select an option > " << std::flush;
    std::cin >> this->menuInput;

    if (menuInput == "1") {
      this->editPatron();
    } else if (menuInput == "2") {
      this->deletePatron();
      keepGoing = false;
    } else if (menuInput == "3") {
      delete this->activeAddress;
      delete this->activePatron;
      keepGoing = false;
    } else {
      this->invalid();
    }
  }

}

//=====================================================================//

void Menu::editPatron() {

  this->res = this->stmt->executeQuery("SELECT * FROM Patrons WHERE cardNumber = '" + this->activePatron->getCardNumber() + "'");
  while(this->res->next()) {
    this->addressId = this->res->getString("address");
    this->patronId = this->res->getString("id");
  }

  std::cout << "|=========================|\n\nEdit patron (Leave blank to remain unchanged)\n\n" << std::endl;

  std::cin.ignore();
  std::cout << "First Name: " << std::flush;
  std::getline(std::cin, this->firstNameInput);

  std::cout << "Last Name: " << std::flush;
  std::getline(std::cin, this->lastNameInput);

  std::cout << "Email: " << std::flush;
  std::getline(std::cin, this->emailInput);

  std::cout << "Card Number: " << std::flush;
  std::getline(std::cin, this->cardInput);

  std::cout << "Street: " << std::flush;
  std::getline(std::cin, this->streetInput);

  std::cout << "City: " << std::flush;
  std::getline(std::cin, this->cityInput);

  std::cout << "State: " << std::flush;
  std::getline(std::cin, this->stateInput);

  std::cout << "Zipcode: " << std::flush;
  std::getline(std::cin, this->zipInput);

  if(this->firstNameInput != "") {
    this->activePatron->setFirstName(this->firstNameInput);
  }
  if(this->lastNameInput != "") {
    this->activePatron->setLastName(this->lastNameInput);
  }
  if(this->cardInput != "") {
    this->activePatron->setCardNumber(this->cardInput);
  }
  if(this->streetInput != "") {
    this->activeAddress->setStreet(this->streetInput);
  }
  if(this->cityInput != "") {
    this->activeAddress->setCity(this->cityInput);
  }
  if(this->stateInput != "") {
    this->activeAddress->setState(this->stateInput);
  }
  if(this->zipInput != "") {
    this->activeAddress->setZipcode(this->zipInput);
  }

  this->updateAddress();
  this->updatePatron();

  this->viewPatron();

}

//=====================================================================//

void Menu::deletePatron() {
  bool keepGoing = true;

  while(keepGoing) {
    std::cout << "Are you sure you want to delete this patron? Y/N > " << std::flush;
    std::cin >> this->deleteInput;

    if (this->deleteInput == "Y") {
      std::cout << "Deleting patron...\n" << std::endl;

      this->res = this->stmt->executeQuery("SELECT * FROM Patrons WHERE cardNumber = '" + this->activePatron->getCardNumber() + "'");

      while (this->res->next()) {
      this->addressId = this->res->getString("address");
      }

      this->stmt->execute("DELETE FROM Patrons WHERE cardNumber = '" + this->activePatron->getCardNumber() + "'");

      this->stmt->execute("DELETE FROM Addresses WHERE id = '" + this->addressId + "'");

      delete this->activePatron;
      delete this->res;

      keepGoing = false;
    } else if (this->deleteInput == "N"){
      std::cout << "Canceling...\n" << std::endl;
      keepGoing = false;
    } else {
      this->invalid();
    }
  }
}

//=====================================================================//

// Material menu methods

void Menu::addMaterial() {
  bool keepGoing = true;

  std::cout << "|=========================|\n\nAdd a new material\n" << std::endl;

  std::cout << "Material ID: " << std::flush;
  std::cin >> this->materialIdInput;

  std::cin.ignore();
  std::cout << "Title: " << std::flush;
  std::getline(std::cin, this->titleInput);

  while(keepGoing) {
    std::cout << "Book/CD/Movie: " << std::flush;
    std::cin >> this->typeInput;
    if (this->typeInput == "book") {
      this->creatorTypeInput = "Author";
      keepGoing = false;
    } else if (this->typeInput == "cd") {
      this->creatorTypeInput = "Singer";
      keepGoing = false;
    } else if (this->typeInput == "movie") {
      this->creatorTypeInput = "Producer";
      keepGoing = false;
    } else {
      this->invalid();
    }
  }

  std::cin.ignore();

  std::cout << this->creatorTypeInput << ": " << std::flush;
  std::getline(std::cin, this->creatorInput);

  std::cout << "Location: " << std::flush;
  std::cin >> this->locationInput;

  this->activeMaterial = new Material(this->materialIdInput, this->titleInput, this->typeInput, this->creatorInput, this->creatorTypeInput, this->locationInput);

  this->insertMaterial();

  this->viewMaterial();
}
//=====================================================================//

void Menu::searchMaterial() {
  bool keepGoing = true;
  while(keepGoing) {
    std::cout << "|=========================|\n\nSearch for existing material \n\nSearch by: \n1) Title \n2) Material Id \n3) Back to patron menu\n" << std::endl;

    std::cout << "Please select an option > " << std::flush;
    std::cin >> this->menuInput;

    if (this->menuInput == "1") {
      std::cin.ignore();
      std::cout << "Title: " << std::flush;
      std::getline(std::cin, this->titleInput);

      // ERROR HANDLING - need to check if Material exists in database at all

      this->res = this->stmt->executeQuery("SELECT * FROM Materials WHERE title = '" + this->titleInput + "'");

      this->createMaterialQuery();

      this->viewMaterial();
      keepGoing = false;

    } else if (this->menuInput == "2") {

      std::cout << "Material ID: " << std::flush;
      std::cin >> this->materialIdInput;

      // ERROR HANDLING - need to check if Material exists in database at all

      this->res = this->stmt->executeQuery("SELECT * FROM Materials WHERE material_id = '" + this->materialIdInput + "'");

      this->createMaterialQuery();

      this->viewMaterial();
      keepGoing = false;

    } else if (this->menuInput == "3") {
      keepGoing = false;
    } else {
      this->invalid();
    }
  }
}

//=====================================================================//

void Menu::viewMaterial() {
  bool keepGoing = true;

  while(keepGoing) {
    std::cout << "|=========================|\n\nView Material\n" << std::endl;

    std::cout << "ID: " << this->activeMaterial->getId() << std::endl;

    std::cout << "Title: " << this->activeMaterial->getTitle() << std::endl;

    std::cout << "Type: " << this->activeMaterial->getType() << std::endl;

    std::cout << this->activeMaterial->getCreatorType() << ": " << this->activeMaterial->getCreator() << std::endl;

    std::cout << "Location: " << this->activeMaterial->getLocation() << std::endl;

    std::cout << "\n\n1) Delete material \n2) Check In \n3) Return to main menu\n" << std::endl;

    std::cout << "Please select an option > " << std::flush;
    std::cin >> this->menuInput;

    if (menuInput == "1") {
      this->deleteMaterial();
    } else if (menuInput == "2") {
      this->checkIn();
      keepGoing = false;
    } else if (menuInput == "3") {
      delete this->activeMaterial;
      keepGoing = false;
    } else {
      this->invalid();
    }
  }

}

//=====================================================================//

void Menu::deleteMaterial() {
  bool keepGoing = true;

  while(keepGoing) {
    std::cout << "Are you sure you want to delete this material? Y/N > " << std::flush;
    std::cin >> this->deleteInput;
    if (this->deleteInput == "Y") {
      std::cout << "Deleting material...\n" << std::endl;

      this->stmt->execute("DELETE FROM Materials WHERE material_id = '" + this->activeMaterial->getId() + "'");

      delete this->activeMaterial;

      keepGoing = false;
    } else if (this->deleteInput == "N"){
      std::cout << "Canceling...\n" << std::endl;
      keepGoing = false;
    } else {
      this->invalid();
    }
  }
}

//=====================================================================//

// SQL Queries

void Menu::insertAddress() {
  this->stmt->execute("INSERT INTO Addresses(street, city, state, zipcode) VALUES ('" + this->streetInput + "', '" + this->cityInput + "', '" + this->stateInput + "', '" + this->zipInput + "')");
}

void Menu::insertPatron() {
  this->stmt->execute("INSERT INTO Patrons(firstName, lastName, cardNumber, email, address) VALUES ('" + this->firstNameInput + "', '" + this->lastNameInput + "', '" + this->cardInput + "', '" + this->emailInput + "', LAST_INSERT_ID())");
}

void Menu::insertMaterial() {
  this->stmt->execute("INSERT INTO Materials(material_id, title, type, location, creator, creator_type) VALUES ('" + this->materialIdInput + "', '" + this->titleInput + "', '" + this->typeInput + "', '" + this->locationInput + "', '" + this->creatorInput + "', '" + this->creatorTypeInput + "')");
}

//=====================================================================//

void Menu::createPatronQuery() {
  while(this->res->next()) {
    this->addressId = this->res->getString("address");
  }

  std::cout << this->addressId << std::endl;

  this->res = this->stmt->executeQuery("SELECT * FROM Addresses WHERE id = '" + this->addressId + "'");

  delete this->activeAddress;
  while(this->res->next()) {
    this->activeAddress = new Address(this->res->getString("street"), this->res->getString("city"), this->res->getString("state"), this->res->getString("zipcode"));
  }

  this->res = this->stmt->executeQuery("SELECT * FROM Patrons WHERE address = '" + this->addressId + "'");

  delete this->activePatron;
  while(this->res->next()) {
    this->activePatron = new Patron(this->res->getString("firstName"), this->res->getString("lastName"), this->res->getString("email"), this->activeAddress, this->res->getString("cardNumber"));
  }
}

//=====================================================================//

void Menu::createMaterialQuery() {
  while(this->res->next()) {
    this->activeMaterial = new Material(this->res->getString("material_id"), this->res->getString("title"), this->res->getString("type"), this->res->getString("creator"), this->res->getString("creator_type"), this->res->getString("location"));
  }

  delete this->res;
}

//=====================================================================//

void Menu::updateAddress() {
  this->stmt->execute("UPDATE Addresses SET street = '" + this->activeAddress->getStreet() + "', city = '" + this->activeAddress->getCity() + "', state = '" + this->activeAddress->getState() + "', zipcode = '" + this->activeAddress->getZipcode() + "' WHERE id = '" + this->addressId + "'");
}

//=====================================================================//

void Menu::updatePatron() {
  this->stmt->execute("UPDATE Patrons SET firstName = '" + this->activePatron->getFirstName() + "', lastName = '" + this->activePatron->getLastName() + "', cardNumber = '" + this->activePatron->getCardNumber() + "', email = '" + this->activePatron->getEmail() + "' WHERE id = '" + this->patronId + "'");
}


//=====================================================================//

// Function to simplify printing an invalid input statement
void Menu::invalid() {
    std::cout << "|=========================|\n\nInvalid input. Try again.\n" << std::endl;
}

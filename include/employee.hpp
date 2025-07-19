#pragma once

#include <string>

#include "manager.hpp"
#include "structs.h"

class Employee {
    public:

    Employee(std::string, std::string, bool);
    Employee(std::string, std::string, std::string);
    ~Employee() = default;

    void sendToDatabase(std::shared_ptr<Manager>);
    int calculateAge();

    std::string getName() { return name; };
    std::string getBirthDate() { return birth_date; };
    bool getGender() { return gender; };

    private:

    std::string name;
    std::string birth_date;
    bool gender;
};
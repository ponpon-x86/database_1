#pragma once

#include <string>

#include "manager.hpp"
#include "structs.h"

class Employee {
    public:

    Employee(std::string, std::string, bool);
    Employee(std::string, std::string, std::string);
    ~Employee() = default;

    bool validate();
    void sendToDatabase(std::shared_ptr<Manager>);
    int calculateAge();

    private:

    std::string name;
    std::string birth_date;
    bool gender;

    bool valid_gender = true;
};
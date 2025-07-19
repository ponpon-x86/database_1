#pragma once

#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <ctime>

#include "structs.h"
#include "employee.hpp"

class Generator {

    public:

    Generator(
        const std::vector<std::string>&,
        const std::vector<std::string>&,
        const std::vector<std::string>&,
        const std::vector<std::string>&
    );
    ~Generator() = default;
    Employee generateEmployee(bool secret = false);

    private:

    int current_year;

    const std::vector<std::string>& names_m;
    const std::vector<std::string>& names_f;
    const std::vector<std::string>& surnames;
    const std::vector<std::string>& secret_surnames;

    std::mt19937 seed;
    std::uniform_int_distribution<int> dist_names_m; 
    std::uniform_int_distribution<int> dist_names_f; 
    std::uniform_int_distribution<int> dist_surnames; 
    std::uniform_int_distribution<int> dist_secret_surnames; 

    std::uniform_int_distribution<int> dist_gender;

    std::uniform_int_distribution<int> dist_year; 
    std::uniform_int_distribution<int> dist_month; 

    std::uniform_int_distribution<int> dist_day_30;
    std::uniform_int_distribution<int> dist_day_31;
    std::uniform_int_distribution<int> dist_day_28;
    std::uniform_int_distribution<int> dist_day_29;
};
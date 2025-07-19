#pragma once

#include <conio.h>
#include <cctype>

#include "manager.hpp"
#include "worker.hpp"
#include "employee.hpp"

class App {

    public:

    App(const std::vector<std::string>&);
    ~App() = default;

    private:

    std::vector<Employee> createEmployeeSubset(const std::vector<std::string>&);

    std::shared_ptr<Manager> manager = std::make_shared<Manager>();
    Worker worker;

    std::vector<Employee> employees;
};
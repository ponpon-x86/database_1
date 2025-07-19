#pragma once

#include <conio.h>
#include <cctype>

#include "manager.hpp"
#include "worker.hpp"
#include "employee.hpp"
#include "generator.hpp"

class App {

    public:

    App(const std::vector<std::string>&);
    ~App() = default;

    private:

    std::vector<Employee> createEmployeeSubset(const std::vector<std::string>&);

    Loader loader;
    std::shared_ptr<Manager> manager;
    Worker worker;
    Generator generator;

    std::vector<Employee> employees;
};
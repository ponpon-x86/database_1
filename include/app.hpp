#pragma once

#include <conio.h>
#include <cctype>

#include "manager.hpp"
#include "worker.hpp"
#include "employee.hpp"

class App {

    public:

    App(char*);
    ~App() = default;

    private:

    std::shared_ptr<Manager> manager = std::make_shared<Manager>();
    Worker worker;

    std::vector<Employee> employees;
};
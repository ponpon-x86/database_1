#pragma once

#include <conio.h>

#include "manager.hpp"
#include "worker.hpp"

class App {

    public:

    App(char*);
    ~App() = default;

    private:

    std::shared_ptr<Manager> manager = std::make_shared<Manager>();
    Worker worker;
};
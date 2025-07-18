#pragma once

#include "manager.hpp"

class Worker {
    public:

    Worker() = default;
    ~Worker() = default;

    void task1(std::shared_ptr<Manager>);
    void task2(std::shared_ptr<Manager>);
    void task3(std::shared_ptr<Manager>);
    void task4(std::shared_ptr<Manager>);
    void task5(std::shared_ptr<Manager>);

    private:


};
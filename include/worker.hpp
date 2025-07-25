#pragma once

#include "manager.hpp"
#include "employee.hpp"

class Worker {
    public:

    Worker() = default;
    ~Worker() = default;

    void task1(std::shared_ptr<Manager>);
    void task2(std::vector<Employee>, std::shared_ptr<Manager>);
    void task3(std::vector<Employee>&, std::shared_ptr<Manager>);
    void task4(std::vector<Employee>&, std::shared_ptr<Manager>);
    std::chrono::milliseconds task5(std::vector<Employee>&, std::shared_ptr<Manager>);
    std::chrono::milliseconds task6(std::vector<Employee>&, std::shared_ptr<Manager>);

    private:
};
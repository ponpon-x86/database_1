#include "app.hpp"

App::App(char* arg) {
    auto input = atoi(arg);
    switch(input) {
        case 1:
        worker.task1(manager);
        break;

        case 2:
        worker.task2(manager);
        break;

        case 3:
        worker.task3(manager);
        break;

        case 4:
        worker.task4(manager);
        break;

        case 5:
        worker.task5(manager);
        break;
    }
}
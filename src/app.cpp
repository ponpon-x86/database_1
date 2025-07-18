#include "app.hpp"

App::App(char* arg) {
    int input;
    std::string checker(arg);

    if (checker.length() == 1 && std::isdigit(checker.front()))
        input = atoi(arg);
    else input = -1;

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
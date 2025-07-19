#include <iostream>

#include "app.hpp"

int main(int argc, char *argv[]) {
    std::vector<std::string> arguments(argv, argv + argc);
    if (argc > 1) App app(argv[1]); else std::cout << "\tError: no parameters provided.\n";
    return 0;
}
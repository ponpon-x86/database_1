#include "app.hpp"

App::App(const std::vector<std::string>& arguments) :
manager(std::make_shared<Manager>(loader.getDBData())),
generator(
    loader.getNamesM(), loader.getNamesF(), 
    loader.getSurnames(), loader.getSecretSurnames()
) {
    // the first argument should be task number;
    // at this point there's at least 2 of them
    // (as confirmed by main.cpp)
    // and we don't need the argument numero 0

    // all arguments after that belong to task 2
    // and follow the pattern: [<name> <date> <gender>]
    int input;
    std::string menu(arguments.at(1));

    // check the validity of task number
    if (menu.length() == 1 && std::isdigit(menu.front()))
        input = atoi(menu.c_str());
    else input = -1;

    switch(input) {
        case 1:
        worker.task1(manager);
        break;

        case 2:
        if (arguments.size() < 5) {
            std::cout << "\tNot enough arguments to start task num.2!\n";
            std::cout << "\tThe correct syntax is: database_1.exe 2 [name] [date] [gender] ...\n";
        }
        else worker.task2(createEmployeeSubset(arguments), manager);
        break;

        case 3:
        worker.task3(employees, manager);
        break;

        case 4:
        for (auto i = 0; i < 1000000; ++i) employees.push_back(generator.generateEmployee());
        for (auto i = 0; i < 100; ++i) employees.push_back(generator.generateEmployee(true));
        worker.task4(employees, manager);
        break;

        case 5:
        worker.task5(manager);
        break;
    }
}

std::vector<Employee> 
App::createEmployeeSubset(const std::vector<std::string>& arguments) {
    // generally, we want to look through tuples
    // of these arguments and validate them;
    // if they are valid, form an Employee and pass
    // to task2, else -- discard them.
    std::vector<Employee> employees_subset;
    for (unsigned i = 0 ; 4 + i * 3 < arguments.size() ; ++i) {
        unsigned name_iter = 2 + i * 3; 
        unsigned date_iter = 3 + i * 3; 
        unsigned gender_iter = 4 + i * 3;

        // since the name can be whatever, there's no point
        // in validating it
        std::string name = arguments.at(name_iter);
        std::cout << "\tTrying to create employee object [" << name << "]...\n";
        // the date, though, can be validated.
        std::string date = arguments.at(date_iter);
        auto date_tuple = common::getYearMonthDay(date);
        if (!common::validateDate(date_tuple)) {
            std::cout << "\n\t\tError gathering input data num." << i << " into new Employee object:\n";
            std::cout << "\t\tthe input date is invalid; be sure to input date as YYYY-MM-DD OR DD-MM-YYYY.\n";
            continue;
        }
        // great, now we get the gender and validate it.
        std::string gender = arguments.at(gender_iter);
        if (!common::validateGender(gender)) {
            std::cout << "\n\t\tError gathering input data num." << i << " into new Employee object:\n";
            std::cout << "\t\tthe gender is invalid. The gender can be assigned in one of the following forms:\n";
            std::cout << "\t\tmale / m / 1 OR female / f / 0.\n";
            continue;
        }
        employees_subset.push_back( { name, date, common::genderStrToBool(gender) } );
    }
    return employees_subset;
}
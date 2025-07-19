#pragma once

#include "worker.hpp"

void Worker::task1(std::shared_ptr<Manager> manager) {
    std::cout << "\tCreating table (if it doesn't exist yet):\n";
    auto connection = manager->establishConnection();
    try {
        pqxx::work work(*connection->getConnection().get());
        work.exec("CREATE TABLE IF NOT EXISTS Employee(id SERIAL PRIMARY KEY, name varchar, birth_date date, gender bool)");
        work.commit();
    } catch (pqxx::sql_error const &e) {
        std::cout << "\tException occured.\n";
        throw e;
    }
    manager->closeConnection(connection);
    std::cout << "\tDone.\n";
}

void Worker::task2(std::vector<Employee> employees, std::shared_ptr<Manager> manager) {
    std::cout << "\tFilling in data about every employee in the subset...\n";
    std::cout << "\t(there are " << employees.size() << " employees correctly filled in)\n";

    std::vector<std::shared_ptr<std::thread>> threads;
    for (auto& employee : employees) {
        // employee.sendToDatabase(manager);
        threads.push_back(std::make_shared<std::thread>(std::thread(&Employee::sendToDatabase, &employee, manager)));
    }

    for (auto& t: threads) {
        t.get()->join();
    }
    std::cout << "\tDone.\n";
}

void Worker::task3(std::vector<Employee>& employees, std::shared_ptr<Manager> manager) {
    std::cout << "\tRetrieving data about every Employee with UNIQUE name AND birth date...\n";
    auto connection = manager->establishConnection();
    pqxx::work work(*connection->getConnection().get());
    pqxx::stream_from stream {
        work, pqxx::from_query,
        "SELECT e.name, e.birth_date, BOOL_OR(e.gender) \
        FROM Employee e \
        GROUP BY name, birth_date \
        ORDER BY name" };
    std::tuple<std::string, std::string, bool> row;
    while (stream >> row) {
        employees.push_back( { std::get<0>(row), std::get<1>(row), std::get<2>(row) } );
    }
    stream.complete();
    manager->closeConnection(connection);

    for(auto& employee: employees) {
        std::cout << "\t-- " << employee.getName() << ", " << 
        (employee.getGender() ? "male" : "female") << 
        " (born " << employee.getBirthDate() << 
        " / " << employee.calculateAge() << " y.o.);\n";
    }

    std::cout << "\tDone.\n";
}

void Worker::task4(std::vector<Employee>& employees, std::shared_ptr<Manager> manager) {
    std::cout << "\tMass insertion of generated employees...\n";
    auto connection = manager->establishConnection();
    pqxx::work work(*connection->getConnection().get());
    try {
        auto stream = pqxx::stream_to::table(
            work,
            { "employee" },
            {"name", "birth_date", "gender"} );
        for (auto &employee: employees)
            stream << std::make_tuple(employee.getName(), employee.getBirthDate(), employee.getGender());
        stream.complete();
    } catch (pqxx::sql_error const &e) {
        std::cout << "\tException occured: " << e.what() << "\n";
        throw e;
    }
    work.commit();
    manager->closeConnection(connection);
    std::cout << "\tDone.\n";
}

void Worker::task5(std::shared_ptr<Manager> manager) {

}
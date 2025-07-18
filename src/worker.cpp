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

void Worker::task2(std::shared_ptr<Manager> manager) {

}

void Worker::task3(std::shared_ptr<Manager> manager) {

}

void Worker::task4(std::shared_ptr<Manager> manager) {

}

void Worker::task5(std::shared_ptr<Manager> manager) {

}
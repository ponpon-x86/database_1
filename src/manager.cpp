#include "manager.hpp"

/*
-----------------------------
Constructor / Destructor
-----------------------------
*/

Manager::Manager(const common::DBData& data) : data(data) {
    createConnectionQueue();
}

void Manager::createConnectionQueue() {
    std::unique_lock<std::mutex> lock(mutex);
    for(unsigned i = 0; i < threads; ++i) {
        connectors.emplace(std::make_shared<Connector>(this->data));
    }
}

std::shared_ptr<Connector> Manager::establishConnection() {
    std::unique_lock<std::mutex> lock(mutex);
    while (connectors.empty()) {
        cv.wait(lock);
    }

    auto new_connection = connectors.front();
    connectors.pop();
    return new_connection;
}

void Manager::closeConnection(std::shared_ptr<Connector> connection) {
    std::unique_lock<std::mutex> lock(mutex);
    connectors.push(connection);
    lock.unlock();
    cv.notify_one();
}
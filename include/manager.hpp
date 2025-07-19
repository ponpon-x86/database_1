#pragma once

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

#include "connector.hpp"
#include "loader.hpp"

class Manager {
    public:

    Manager(const common::DBData& data);
    ~Manager() = default;

    std::shared_ptr<Connector> establishConnection();
    void closeConnection(std::shared_ptr<Connector>);

    private:

    void createConnectionQueue();

    const common::DBData& data;
    std::queue<std::shared_ptr<Connector>> connectors;

    unsigned const threads = 4;
    std::mutex mutex;
    std::condition_variable cv;
};
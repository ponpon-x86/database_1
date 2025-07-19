#pragma once

// #include <mysqlx/xdevapi.h>
// #include <mysql/jdbc.h>

#include "loader.hpp"
#include "structs.h"

#include <pqxx/pqxx>

class Connector {
    public:

    Connector(const common::DBData&);
    ~Connector() = default;
    std::shared_ptr<pqxx::connection> getConnection();

    private:

    std::string url;
    std::shared_ptr<pqxx::connection> connection;
};
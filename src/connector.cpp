#include "connector.hpp"

Connector::Connector(DBData data) {
    url = "host=" + data.host_name + " port=" + std::to_string(data.port) + " dbname=" + data.database + 
        " user=" + data.user_name + " password=" + data.password;

    connection = std::make_shared<pqxx::connection>(url);
}

std::shared_ptr<pqxx::connection> Connector::getConnection() {
    return connection;
}
#include "loader.hpp"

Loader::Loader() {
    loadData();
}

void Loader::loadData() {
    // read file
    std::ifstream file("../../settings.json");
    if (!file.is_open()) {
        std::cout << "\tsettings.json file is missing.\n";
        exit(1);
    }
    std::string json((
        std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    // create a document
    rapidjson::Document document;
    // parse it
    document.Parse(json.c_str());

    if (document.HasParseError()) {
        std::cout << "\tError parsing settings.json: " << document.GetParseError() << "\n";
        exit(1);
    }
    
    data.host_name = this->stringify(document["host_name"]);
    data.user_name = this->stringify(document["user_name"]);
    data.password = this->stringify(document["password"]);
    data.database = this->stringify(document["database"]);
    data.port = document["port"].GetInt();
}

std::string Loader::stringify(const rapidjson::Value& val) const {
    return val.GetString();
}

common::DBData Loader::getDBData() const {
    return data;
}
#include "loader.hpp"

Loader::Loader() {
    loadData();
}

void Loader::loadData() {    
    // let's speed this up...
    std::vector<std::shared_ptr<std::thread>> threads;
    threads.push_back(std::make_shared<std::thread>(&Loader::loadSettings, this, "../../settings.json"));
    threads.push_back(std::make_shared<std::thread>(&Loader::loadNames, this, "../../extern/resources/male.names", std::ref(names_m)));
    threads.push_back(std::make_shared<std::thread>(&Loader::loadNames, this, "../../extern/resources/female.names",  std::ref(names_f)));
    threads.push_back(std::make_shared<std::thread>(&Loader::loadNames, this, "../../extern/resources/sur.names",  std::ref(surnames)));
    threads.push_back(std::make_shared<std::thread>(&Loader::loadNames, this, "../../extern/resources/secret_sur.names",  std::ref(secret_surnames)));

    for(auto& t: threads)
        t.get()->join();
} 

void Loader::loadNames(std::string filename, std::vector<std::string>& where) {
    // "../../extern/resources/male.names"
    std::ifstream file(filename);
    if(!file.is_open()) {
        std::cout << "\tFatal error: file [" << filename << "] is missing.\n";
        exit(1);
    }

    std::string line;
    while(std::getline(file, line)) {
        where.push_back(line);
    }
}

void Loader::loadSettings(std::string filename) {
    // read file
    // "../../settings.json"
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "\tFatal error: file [" << filename << "] is missing.\n";
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
        std::cout << "\tError parsing file [" << filename << "]: " << document.GetParseError() << "\n";
        exit(1);
    }
    
    data.host_name = this->stringify(document["host_name"]);
    data.user_name = this->stringify(document["user_name"]);
    data.password = this->stringify(document["password"]);
    data.database = this->stringify(document["database"]);
    data.port = document["port"].GetInt();

    file.close();
}

std::string Loader::stringify(const rapidjson::Value& val) const {
    return val.GetString();
}

const common::DBData& Loader::getDBData() const {
    return data;
}
#pragma once

#include <document.h>

#include <fstream>
#include <iostream>
#include <thread>

#include "structs.h"

class Loader {
    public:
    
    Loader();
    ~Loader() = default;

    const common::DBData& getDBData() const;

    const std::vector<std::string>& getNamesM() const { return names_m; } ;
    const std::vector<std::string>& getNamesF() const { return names_f; } ;
    const std::vector<std::string>& getSurnames() const { return surnames; } ;
    const std::vector<std::string>& getSecretSurnames() const { return secret_surnames; } ;

    private:

    void loadData();

    void loadSettings(std::string filename);
    void loadNames(std::string filename, std::vector<std::string>& where);

    common::DBData data;
    std::string stringify(const rapidjson::Value&) const;

    std::vector<std::string> names_m;
    std::vector<std::string> names_f;
    std::vector<std::string> surnames;
    std::vector<std::string> secret_surnames;
};
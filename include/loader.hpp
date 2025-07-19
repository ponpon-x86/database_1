#pragma once

#include <document.h>

#include <fstream>
#include <iostream>

#include "structs.h"

class Loader {
    public:
    
    Loader();
    ~Loader() = default;

    common::DBData getDBData() const;

    private:

    void loadData();

    common::DBData data;
    std::string stringify(const rapidjson::Value&) const;
};
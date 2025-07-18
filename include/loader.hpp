#pragma once

#include <document.h>

#include <fstream>
#include <iostream>

#include "structs.h"

class Loader {
    public:
    
    Loader();
    ~Loader() = default;

    DBData getDBData() const;

    private:

    DBData data;
    std::string stringify(rapidjson::Value&) const;
};
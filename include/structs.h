#pragma once

#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>

namespace common {
    struct DBData {
        std::string host_name;
        std::string user_name;
        std::string password;
        std::string database;
        int port;
    };

    inline std::tuple<int, int, int> getTodaysDate() {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        return std::make_tuple(1900 + tm.tm_year, 1 + tm.tm_mon, tm.tm_mday);
    }

    inline std::tuple<int, int, int> getYearMonthDay(std::string date) {
        std::tm t = {};
        std::stringstream ss(date);
        ss >> std::get_time(&t, "%Y-%m-%d");
        return std::make_tuple(1900 + t.tm_year, 1 + t.tm_mon, t.tm_mday);
    }

    inline bool validateDate(std::tuple<int, int, int> date) {
        auto year = std::get<0>(date);
        auto month = std::get<1>(date);
        auto day = std::get<2>(date);

        auto todays_year = std::get<0>(getTodaysDate());

        // Check year range
        if (year < 1000 || year > todays_year) {
            return false;
        }
        // Check month range
        if (month < 1 || month > 12) {
            return false;
        }
        // Check day range
        if (day < 1 || day > 31) {
            return false;
        }

        // Handle months with 30 days
        if (month == 4 || month == 6 || month == 9 || month == 11) {
            if (day > 30) {
                return false;
            }
        }

        // February
        if (month == 2) {
            if ([year]() { return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0); }()) { // check the leap year
                if (day > 29) {
                    return false;
                }
            } else {
                if (day > 28) {
                    return false;
                }
            }
        }

        return true; // valid
    }
};
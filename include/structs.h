#pragma once

#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <regex>

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
        #pragma warning(suppress : 4996)
        auto tm = *std::localtime(&t);

        return std::make_tuple(1900 + tm.tm_year, 1 + tm.tm_mon, tm.tm_mday);
    }

    inline std::tuple<int, int, int> getYearMonthDay(std::string& date) {
        // alright, so, we can validate the string format with a regex.
        // unfortunately.
        // this should do it:
        std::regex pattern(R"(^(\d+)-(\d+)-(\d+)$)");
        std::smatch matches;

        if (std::regex_match(date, matches, pattern)) {
            // so now we will just assume that if number 3 is 4 symbols wide
            // it's the year.
            int number1 = std::stoi(matches[1].str());
            int number2 = std::stoi(matches[2].str());
            int number3 = std::stoi(matches[3].str());
            if (matches[3].str().length() == 4) {
                date = matches[3].str() + "-" + matches[2].str() + "-" + matches[1].str();
                return std::make_tuple(number3, number2, number1); // Y M D
            }
            else // else assume the date is in Y-M-D format anyway
                return std::make_tuple(number1, number2, number3); // Y M D
        }

        // if regex did not match, the input should be invalid, so lets just...
        return std::make_tuple(-1, -1, -1);

        /*
        std::tm t = {};
        std::stringstream ss(date);
        ss >> std::get_time(&t, "%Y-%m-%d");
        return std::make_tuple(1900 + t.tm_year, 1 + t.tm_mon, t.tm_mday);
        */
    }

    inline bool validateDate(const std::tuple<int, int, int>& date) {
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

    inline bool validateGender(const std::string& gender) {
        if (gender == "1" || gender == "0")
            return true;

        std::string t = gender;
        std::transform(t.begin(), t.end(), t.begin(),
            [](unsigned char c){ return std::tolower(c); });

        if (t == "male" || t == "m" || t == "female" || t == "f")
            return true;

        return false;
    }

    inline bool genderStrToBool(const std::string& gender) {
        if (gender == "1") return true;
        if (gender == "0") return false;

        std::string t = gender;
        std::transform(t.begin(), t.end(), t.begin(),
            [](unsigned char c){ return std::tolower(c); });

        if (t == "male" || t == "m")
            return true;
        if (t == "female" || t == "f")
            return false;

        return false;
    }
};
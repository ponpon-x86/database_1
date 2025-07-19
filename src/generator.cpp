#include "generator.hpp"

Generator::Generator(
    const std::vector<std::string>& names_m,
    const std::vector<std::string>& names_f,
    const std::vector<std::string>& surnames,
    const std::vector<std::string>& secret_surnames
) : names_m(names_m), names_f(names_f), surnames(surnames), secret_surnames(secret_surnames) {
    dist_names_m = std::uniform_int_distribution<int>(0, static_cast<int>(names_m.size()) - 1);
    dist_names_f = std::uniform_int_distribution<int>(0, static_cast<int>(names_f.size()) - 1);
    dist_surnames = std::uniform_int_distribution<int>(0, static_cast<int>(surnames.size()) - 1);
    dist_secret_surnames = std::uniform_int_distribution<int>(0, static_cast<int>(secret_surnames.size()) - 1);

    dist_gender = std::uniform_int_distribution<int>(0, 1);

    auto today = common::getTodaysDate();
    current_year = std::get<0>(today);
    dist_year = std::uniform_int_distribution<int>(current_year - 60, current_year - 18);
    dist_month = std::uniform_int_distribution<int>(1, 12);

    dist_day_28 = std::uniform_int_distribution<int>(1, 28);
    dist_day_29 = std::uniform_int_distribution<int>(1, 29);
    dist_day_30 = std::uniform_int_distribution<int>(1, 30);
    dist_day_31 = std::uniform_int_distribution<int>(1, 31);
    seed.seed(std::random_device{}());
}

Employee Generator::generateEmployee(bool secret) {
    auto surname = secret ? secret_surnames.at(dist_secret_surnames(seed)) :
        surnames.at(dist_surnames(seed));

    auto gender_var = dist_gender(seed);
    bool gender = secret ? 1 : !!gender_var;

    auto name = gender ? names_m.at(dist_names_m(seed)) :
        names_f.at(dist_names_f(seed));

    auto year = dist_year(seed);
    auto month = dist_month(seed);

    int day;
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        day = dist_day_30(seed);
    }
    else if (month == 2) {
        if ([year]() { return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0); }()) { // check the leap year
            day = dist_day_29(seed);
        } else {
            day = dist_day_28(seed);
        }
    }
    else day = dist_day_31(seed);

    return {
        surname + " " + name,
        std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day),
        gender
    };
}
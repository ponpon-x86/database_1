#include "employee.hpp"

Employee::Employee(std::string name, std::string birth_date, bool gender) :
name(name), birth_date(birth_date), gender(gender) {
    
}

Employee::Employee(std::string name, std::string birth_date, std::string gender) :
name(name), birth_date(birth_date), gender(validateGender(gender)) {

}

bool Employee::validateGender(std::string gender_str) {
    std::string t = gender_str;
    std::transform(t.begin(), t.end(), t.begin(),
        [](unsigned char c){ return std::tolower(c); });

    if (t == "male" || t == "m")
        return true;
    else if (t == "female" || t == "f")
        return false;
    else valid_gender = false;

    return false;
}

bool Employee::validate() {
    if (!valid_gender)
        return false;
    if (!common::validateDate(common::getYearMonthDay(this->birth_date)))
        return false;
    return true;
}

void Employee::sendToDatabase(std::shared_ptr<Manager> manager) {
    std::cout << "\tSending data of employee " << name << " (born " << birth_date <<
    "), " << (this->gender? "male" : "female") << " to the database.\n";

    auto bday = common::getYearMonthDay(this->birth_date);
    auto date_str = 
        std::to_string(std::get<0>(bday)) + "-" +
        std::to_string(std::get<1>(bday)) + "-" +
        std::to_string(std::get<2>(bday));

    auto connection = manager->establishConnection();

    try {
        pqxx::work work(*connection->getConnection().get());
        work.exec("INSERT INTO Employee VALUES (DEFAULT, '" + 
            this->name + "', '" + date_str +
            "', " + (this->gender? "true" : "false") + ")");
        work.commit();
    } catch (pqxx::sql_error const &e) {
        std::cout << "\tException occured.\n";
        throw e;
    }

    manager->closeConnection(connection);
    std::cout << "\tDone.\n";
}

int Employee::calculateAge() {
    auto tupled_birthday_date = common::getYearMonthDay(this->birth_date);
    auto tupled_today_date = common::getTodaysDate();

    if ( std::get<0>(tupled_today_date) <= std::get<0>(tupled_birthday_date) ) // years
        return 0;
    auto years = std::get<0>(tupled_today_date) - std::get<0>(tupled_birthday_date);
    if ( std::get<1>(tupled_today_date) > std::get<1>(tupled_birthday_date) ) // months
        return years;
    if ( std::get<2>(tupled_today_date) > std::get<2>(tupled_birthday_date) ) // days
        return years;
    return years - 1;
}
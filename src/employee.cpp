#include "employee.hpp"

Employee::Employee(std::string name, std::string birth_date, bool gender) :
name(name), birth_date(birth_date), gender(gender) {
    
}

Employee::Employee(std::string name, std::string birth_date, std::string gender) :
name(name), birth_date(birth_date), gender(common::genderStrToBool(gender)) {

}

void Employee::sendToDatabase(std::shared_ptr<Manager> manager) {
    // kind of a bad idea to print these if there are threads.

    /*
    std::cout << "\tSending data of employee " << name << ", " << (this->gender? "male" : "female") << " (born " << birth_date <<
    "), " << "to the database.\n";
    */

    auto connection = manager->establishConnection();

    try {
        pqxx::work work(*connection->getConnection().get());
        work.exec("INSERT INTO Employee VALUES (DEFAULT, '" + 
            this->name + "', '" + this->birth_date +
            "', " + (this->gender? "true" : "false") + ")");
        work.commit();
    } catch (pqxx::sql_error const &e) {
        std::cout << "\tException occured.\n";
        throw e;
    }

    manager->closeConnection(connection);
    // std::cout << "\tDone.\n";
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
#include "employee.hpp"

Employee::Employee(std::string name, std::string birth_date, bool gender) :
name(name), birth_date(birth_date), gender(gender) {
    
}

Employee::Employee(std::string name, std::string birth_date, std::string gender) :
name(name), birth_date(birth_date), gender(gender) {
    std::string t = gender;
    std::transform(t.begin(), t.end(), t.begin(),
        [](unsigned char c){ return std::tolower(c); });

    if (t == "male" || t == "m")
        gender = true;
    else if (t == "female" || t == "f")
        gender = false;
    else valid_gender = false;
}

bool Employee::validate() {
    if (!valid_gender)
        return false;
    if (!common::validateDate(this->birth_date))
        return false;
}

void Employee::sendToDatabase(std::shared_ptr<Manager> manager) {
    std::cout << "\tSending data of employee " << name << " (born " << birth_date <<
    "), " << gender? "male" : "female" << " to the database.\n";

    auto bday = common::getYearMonthDay(this->birth_date);
    auto date_str = 
        std::to_string(bday<0>) + "-" +
        std::to_string(bday<1>) + "-" +
        std::to_string(bday<2>);

    auto connection = manager->establishConnection();

    try {
        pqxx::work work(*connection->getConnection().get());
        work.exec("INSERT INTO Employee VALUES (DEFAULT, '" << this->name "', '" << date_str << "', " << this->gender ")");
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

    if ( tupled_today_date<0> <= tupled_birthday_date<0> ) // years
        return 0;
    auto years = tupled_today_date<0> - tupled_birthday_date<0>;
    if ( tupled_today_date<1> > tupled_birthday_date<1> ) // months
        return years;
    if ( tupled_today_date<2> > tupled_birthday_date<2> ) // days
        return years;
    return years - 1;
}
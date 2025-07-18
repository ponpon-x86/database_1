file(GLOB_RECURSE SOURCES *.cpp)

# set(mysql-concpp_DIR "../extern/mysql-connector-cpp")
# find_package(mysql-concpp REQUIRED release)

add_executable(database_1 ${SOURCES})

set(PostgreSQL_ADDITIONAL_VERSIONS "13" "14" "15" "16" "17")
find_package(PostgreSQL REQUIRED)

find_package(libpqxx REQUIRED)
target_link_libraries(database_1 libpqxx::pqxx)

# target_link_libraries(database_1 mysql::concpp)

target_include_directories(database_1 PUBLIC ../include)
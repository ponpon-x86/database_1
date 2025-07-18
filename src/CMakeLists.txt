file(GLOB_RECURSE SOURCES *.cpp)

add_executable(database_1 ${SOURCES})

target_include_directories(spider-solitaire PUBLIC ../include)

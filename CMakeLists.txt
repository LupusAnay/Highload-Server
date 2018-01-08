cmake_minimum_required(VERSION 3.8)
project(Highload_Server)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost COMPONENTS system filesystem thread REQUIRED)

include_directories(${BOOST_INCLUDE_DIRS})

set(SOURCE_FILES
        main.cpp
        Server.cpp Server.h
        Connection.cpp Connection.h
        HTTPHandler.cpp HTTPHandler.h
        Data.cpp Data.h
        sqlite3.c sqlite3.h)

add_executable(Highload_Server ${SOURCE_FILES})

target_link_libraries(Highload_Server
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        pthread
        boost_thread
        boost_regex
        dl)
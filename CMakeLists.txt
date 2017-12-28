
cmake_minimum_required(VERSION 3.8)
project(Highload_Server)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "/home/lupusanay/CLionProjects/Highload Server")
set(SOURCE_FILES
        main.cpp
        Server.cpp Server.h
        Connection.cpp Connection.h)

find_package(Boost COMPONENTS system filesystem thread REQUIRED)
include_directories(${BOOST_INCLUDE_DIRS} ${LIBEVENT_INCLUDE_DIR})

add_executable(Highload_Server ${SOURCE_FILES})

target_link_libraries(Highload_Server
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        pthread
        boost_thread)
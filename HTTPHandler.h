//
// Created by lupusanay on 28.12.17.
//

#ifndef HIGHLOAD_SERVER_HTTPHANDLER_H
#define HIGHLOAD_SERVER_HTTPHANDLER_H


#include <boost/array.hpp>

class HTTPHandler {

public:
    explicit HTTPHandler(char *string);

    boost::array<char, 4096> getResponse();
};


#endif //HIGHLOAD_SERVER_HTTPHANDLER_H

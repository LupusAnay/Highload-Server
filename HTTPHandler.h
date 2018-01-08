//
// Created by lupusanay on 28.12.17.
//

#ifndef HIGHLOAD_SERVER_HTTPHANDLER_H
#define HIGHLOAD_SERVER_HTTPHANDLER_H

#include <boost/asio.hpp>
#include <iostream>
#include <boost/regex.hpp>
#include "Data.h"

using namespace std;
using namespace boost::asio;

class HTTPHandler {

public:
    explicit HTTPHandler(const string &requestData);

    string getResponse();

private:
    struct Request {
        string method;
        string request_target;
        string http_version;
        vector<string> headers;
        string body;
    } request;

    string response = "HTTP/1.1 200 OK\r\n"
            "Server: Custom/0.0.1\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "Accept-Ranges: bytes\r\n\r\n"
            "Hello everyone, it's my new web server!";

    void createResponse();

    void notFound();

    void badRequest();
};


#endif //HIGHLOAD_SERVER_HTTPHANDLER_H

//
// Created by lupusanay on 28.12.17.
//

#ifndef HIGHLOAD_SERVER_HTTPHANDLER_H
#define HIGHLOAD_SERVER_HTTPHANDLER_H

#include <boost/asio.hpp>
#include <iostream>
#include <regex>

using namespace std;
using namespace boost::asio;

class HTTPHandler {

public:
    explicit HTTPHandler(const string &requestData);

    string getResponse();

private:
    map<string, map<string, string>> request = {
            {"Request-Line",
                             {
                                     {"Method",        ""},
                                     {"Request-URI",      ""},
                                     {"HTTP-Version",     ""}
                             }
            },
            {"General-Headers",
                             {
                                     {"Cache-Control", ""},
                                     {"Connection",       ""},
                                     {"Date",             ""},
                                     {"Pragma",          ""},
                                     {"Trailer",          ""},
                                     {"Transfer-Encoding", ""},
                                     {"Upgrade",       ""},
                                     {"Via",          ""},
                                     {"Warning",  ""},
                                     {"Upgrade-Insecure-Requests", ""}
                             }},
            {"Request-Headers",
                             {
                                     {"Accept",        ""},
                                     {"Accept-Charset",   ""},
                                     {"Accept-Encoding",  ""},
                                     {"Accept-Language", ""},
                                     {"Authorization",    ""},
                                     {"Expect",            ""},
                                     {"From",          ""},
                                     {"Host",         ""},
                                     {"If-Match", ""},
                                     {"If-Modified-Since",         ""},
                                     {"If-None-Match", ""},
                                     {"If-Range", ""},
                                     {"If-Unmodified-Since", ""},
                                     {"Max-Forwards", ""},
                                     {"Proxy-Authorization", ""},
                                     {"Range", ""},
                                     {"Referer", ""},
                                     {"TE", ""},
                                     {"User-Agent", ""}
                             }},
            {"Entity-Headers",
                             {
                                     {"Allow",         ""},
                                     {"Content-Encoding", ""},
                                     {"Content-Language", ""},
                                     {"Content-Length",  ""},
                                     {"Content-Location", ""},
                                     {"Content-MD5",       ""},
                                     {"Content-Range", ""},
                                     {"Content-Type", ""},
                                     {"Expires",  ""},
                                     {"Last-Modified",             ""}
                             }},
            {"Request-Body", {}}
    };
    string response = "HTTP/1.1 200 OK\r\n"
            "Server: Custom/0.0.1\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "Accept-Ranges: bytes\r\n\r\n"
            "Hello everyone, it's my new web server!";

    void createResponse();

    void notFound();

    bool validate();

    void badRequest();
};


#endif //HIGHLOAD_SERVER_HTTPHANDLER_H

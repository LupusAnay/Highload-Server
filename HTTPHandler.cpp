//
// Created by lupusanay on 28.12.17.
//

#include "HTTPHandler.h"

vector<string> split(const string &str, const string &exp) {
    vector<string> split_result;
    regex reg(exp);
    sregex_token_iterator iter(str.begin(), str.end(), reg, -1);
    sregex_token_iterator end;
    while(iter != end)
    {
        if(*iter != "")  //If this place in input string isn't empty push a part of the string
            split_result.push_back(*iter);
        ++iter;
    }
    split_result.emplace_back("");
    return split_result;
}

HTTPHandler::HTTPHandler(const string &requestData) {
    try {
        /*
         * GET / HTTP/1.1
         * Host: localhost:5556
         * User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:57.0) Gecko/20100101 Firefox/57.0
         * Accept: text/html,application/xhtml+xml,application/xml;q=0.9,**;q=0.8
         * Accept-Language: ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3
         * Accept-Encoding: gzip, deflate
         * Connection: keep-alive
         * Upgrade-Insecure-Requests: 1
         */
        vector<string> requestLines = split(requestData, "\r\n\r\n");

        request.find("Request-Body")->second.insert(pair<string,string>("Body", requestLines.at(1)));

        vector<string> headersLines = split(requestLines.at(0), "\r\n");

        requestLines.clear();
        vector<string> requestLineItems = split(headersLines.at(0), " ");

        headersLines.erase(headersLines.begin());

        request.find("Request-Line")->second.find("Method")->second = requestLineItems.at(0);
        request.find("Request-Line")->second.find("Request-URI")->second = requestLineItems.at(1);
        request.find("Request-Line")->second.find("HTTP-Version")->second = requestLineItems.at(2);

        for(auto &i : headersLines) {
            string headerName = i.substr(0, i.find(':'));
            for(auto &headerType : request) {
                for(auto &header : headerType.second) {
                    if(headerName == header.first) {
                        cout << "Found: " << headerName << ":" << i.substr(i.find(':') + 1, i.size()) << endl;
                        header.second = i.substr(i.find(':') + 1, i.size());
                    }
                }
            }
        }
    }
    catch (exception &e) {
        cout << "Exception: " << e.what() << endl;
        response = "HTTP/1.1 400 Bad Request\r\n"
                   "Server: Custom/0.0.1\r\n"
                   "Date: Sat, 30 Jan 2017 21:31:46 GMT\r\n"
                   "Content-Type: text/html\r\n"
                   "Content-Length: 4096\r\n"
                   "Last-Modified: Sat, 08 Mar 2014 22:53:30 GMT\r\n"
                   "Connection: close\r\n"
                   "Accept-Ranges: bytes\r\n\r\n"
                   "<html>"
                   "<head><title>400 Bad Request</title></head>"
                   "<body bgcolor=\"white\">"
                   "<center><h1>400 Bad Request</h1></center>"
                   "<hr><center>Custom</center>"
                   "</body>"
                   "</html>";
    }
}

string HTTPHandler::getResponse() {
    return response;
}

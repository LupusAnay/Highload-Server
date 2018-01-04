//
// Created by lupusanay on 28.12.17.
//

#include "HTTPHandler.h"

vector<string> split(const string &str, const string &exp) {
    vector<string> split_result;
    regex reg(exp);
    sregex_token_iterator iter(str.begin(), str.end(), reg, -1);
    sregex_token_iterator end;
    while (iter != end) {
        if (*iter != "")  //If this place in input string isn't empty push a part of the string
            split_result.push_back(*iter);
        ++iter;
    }
    split_result.emplace_back("");
    return split_result;
}

HTTPHandler::HTTPHandler(const string &requestData) {
    try {
        vector<string> requestLines = split(requestData, "\r\n\r\n");

        request.find("Request-Body")->second.insert(pair<string, string>("Body", requestLines.at(1)));

        vector<string> headersLines = split(requestLines.at(0), "\r\n");

        requestLines.clear();
        vector<string> requestLineItems = split(headersLines.at(0), " ");

        headersLines.erase(headersLines.begin());

        request.find("Request-Line")->second.find("Method")->second = requestLineItems.at(0);
        request.find("Request-Line")->second.find("Request-URI")->second = requestLineItems.at(1);
        request.find("Request-Line")->second.find("HTTP-Version")->second = requestLineItems.at(2);

        for (auto &i : headersLines) {
            string headerName = i.substr(0, i.find(':'));
            for (auto &headerType : request) {
                for (auto &header : headerType.second) {
                    if (headerName == header.first) {
                        header.second = i.substr(i.find(':') + 1, i.size());
                    }
                }
            }
        }
        if (validate()) {
            createResponse();
        }
    }
    catch (exception &e) {
        cout << "Exception: " << e.what() << endl;
        badRequest();
    }
}

string HTTPHandler::getResponse() {
    return response;
}

void HTTPHandler::createResponse() {
    string method = request.find("Request-Line")->second.find("Method")->second;
    string uri = request.find("Request-Line")->second.find("Request-URI")->second;
    string body = request.find("Request-Body")->second.find("Body")->second;
    response = "HTTP/1.1 200 OK\r\n"
            "Server: Custom/0.0.1\r\n"
            "Content-Type: application/json\r\n"
            "Connection: close\r\n"
            "Accept-Ranges: bytes\r\n\r\n";

    Data dataProcessor;

    vector<string> uriRes = split(uri, "/api/|/");
    if (method == "GET" && uriRes.size() == 1) {
        response += dataProcessor.getAll(uriRes[0]);
    } else if (method == "GET" && uriRes.size() == 2) {
        response += dataProcessor.getByID(uriRes[0], uriRes[1]);
    } else if (method == "POST" && uriRes.size() == 1) {
        response += dataProcessor.addRow(uriRes[0], body);
    } else if (method == "POST" && uriRes.size() == 2) {
        response += dataProcessor.update(uriRes[0], uriRes[1], body);
    } else if (method == "DELETE" && uriRes.size() == 2) {
        response += dataProcessor.deleteRow(uriRes[0], uriRes[1]);
    } else {
        notFound();
    }
}

void HTTPHandler::notFound() {
    response =
            "HTTP/1.1 404 Not Found\r\n"
                    "Server: Custom/0.0.1\r\n"
                    "Content-Type: text/html\r\n"
                    "Connection: close\r\n"
                    "Accept-Ranges: bytes\r\n\r\n"
                    "<html>"
                    "<head><title>404 Not Found</title></head>"
                    "<body>"
                    "<h1>404 Not Found</h1>"
                    "</body>"
                    "</html>";
}

void HTTPHandler::badRequest() {
    response = "HTTP/1.1 400 Bad Request\r\n"
            "Server: Custom/0.0.1\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "Accept-Ranges: bytes\r\n\r\n"
            "<html>"
            "<head><title>400 Bad Request</title></head>"
            "<body>"
            "<h1>400 Bad Request</h1>"
            "</body>"
            "</html>";
}

bool HTTPHandler::validate() {
    string method = request.find("Request-Line")->second.find("Method")->second;
    string uri = request.find("Request-Line")->second.find("Request-URI")->second;

    if (!regex_match(method, regex("GET|DELETE|POST|HEAD|PUT|CONNECT|OPTIONS|TRACE|PATCH"))) {
        badRequest();
        return false;
    } else if (!regex_match(method, regex("GET|DELETE|POST"))) {
        notFound();
        return false;
    } else if (!regex_match(uri, regex("/api/[a-z0-9_]+/[0-9]+|/api/[a-z0-9_]+"))) {
        notFound();
        return false;
    } else {
        return true;
    }
}



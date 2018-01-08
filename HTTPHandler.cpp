//
// Created by lupusanay on 28.12.17.
//

#include "HTTPHandler.h"

HTTPHandler::HTTPHandler(const string &raw_request) {
    try {
        boost::asio::streambuf request_input_buffer;

        std::ostream request_input_stream(&request_input_buffer);
        request_input_stream << raw_request;

        std::istream request_output_stream(&request_input_buffer);
        request_output_stream >> request.method >> request.request_target >> request.http_version;
        if (!request_output_stream || request.http_version.substr(0, 5) != "HTTP/") {
            cout << "Invalid request" << endl;
            badRequest();
        }

        string header;
        while (getline(request_output_stream, header)) {
            request.headers.push_back(header);
        }

        request.body = "";
        string body_part;
        while (getline(request_output_stream, body_part)) {
            request.body += body_part;
        }
        createResponse();
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
    response = "HTTP/1.1 200 OK\r\n"
            "Server: Custom/0.0.1\r\n"
            "Content-Type: application/json\r\n"
            "Connection: close\r\n"
            "Accept-Ranges: bytes\r\n\r\n";

    Data dataProcessor;
    if (boost::regex_match(request.request_target, boost::regex("/api/[a-z0-9_]+/[0-9]+|/api/[a-z0-9_]+"))) {
        vector<string> uriRes;
        boost::regex reg("/|/api/");
        boost::sregex_token_iterator iter(request.request_target.begin(), request.request_target.end(), reg, -1);
        boost::sregex_token_iterator end;
        while (iter != end) {
            if (*iter != "")
                uriRes.push_back(*iter);
            ++iter;
        }

        if (request.method == "GET" && uriRes.size() == 1) {
            response += dataProcessor.getAll(uriRes[0]);
        } else if (request.method == "GET" && uriRes.size() == 2) {
            response += dataProcessor.getByID(uriRes[0], uriRes[1]);
        } else if (request.method == "POST" && uriRes.size() == 1) {
            response += dataProcessor.addRow(uriRes[0], request.body);
        } else if (request.method == "POST" && uriRes.size() == 2) {
            response += dataProcessor.update(uriRes[0], uriRes[1], request.body);
        } else if (request.method == "DELETE" && uriRes.size() == 2) {
            response += dataProcessor.deleteRow(uriRes[0], uriRes[1]);
        }
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

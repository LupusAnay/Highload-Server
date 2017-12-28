//
// Created by lupusanay on 27.12.17.
//

#ifndef HIGHLOAD_SERVER_SERVER_H
#define HIGHLOAD_SERVER_SERVER_H

#include <vector>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include "Connection.h"

using namespace std;
using namespace boost::asio;

class Server : private boost::noncopyable {

public:
    Server(unsigned short port, unsigned short thread_count);

private:
    io_service service;

    ip::tcp::acceptor acceptor;

    vector<boost::shared_ptr<boost::thread>> threads;

    boost::shared_ptr<Connection> newConnection;

    void startAccept();

    void handleAccept(boost::system::error_code const &error);
};


#endif //HIGHLOAD_SERVER_SERVER_H

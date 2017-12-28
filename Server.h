//
// Created by lupusanay on 27.12.17.
//

#ifndef HIGHLOAD_SERVER_SERVER_H
#define HIGHLOAD_SERVER_SERVER_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "Connection.h"

using namespace std;
using namespace boost::asio;

class Server : private boost::noncopyable {

public:
    Server(unsigned short port, unsigned short thread_count);

    ~Server();

private:
    typedef boost::shared_ptr<boost::thread> threadPtr;
    typedef vector<threadPtr> threadPool;
    typedef boost::shared_ptr<Connection> connectionPtr;

    io_service service;

    ip::tcp::acceptor acceptor;

    connectionPtr newConnection;

    threadPool threads;

    void startAccept();

    void handleAccept(const boost::system::error_code &error);
};


#endif //HIGHLOAD_SERVER_SERVER_H

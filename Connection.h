//
// Created by lupusanay on 27.12.17.
//

#ifndef HIGHLOAD_SERVER_CONNECTION_H
#define HIGHLOAD_SERVER_CONNECTION_H

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace std;
using namespace boost::asio;

class Connection : private boost::noncopyable, public boost::enable_shared_from_this<Connection> {
public:
    explicit Connection(io_service &service);

    ip::tcp::socket &getSocket();

    void start();

private:
    ip::tcp::socket socket;
    io_service::strand strand;
    boost::array<char, 4096> buffer;

    void handleRead(boost::system::error_code const &error, size_t bytes);

    void handleWrite(boost::system::error_code const &error);
};


#endif //HIGHLOAD_SERVER_CONNECTION_H

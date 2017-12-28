//
// Created by lupusanay on 27.12.17.
//

#include "Server.h"

Server::Server(unsigned short port, unsigned short thread_count) :
        acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), port)),
        threads(thread_count) {
    acceptor.set_option(ip::tcp::acceptor::reuse_address(true));
    acceptor.listen();
    startAccept();

    generate(threads.begin(), threads.end(),
             boost::bind(
                     &boost::make_shared<boost::thread, boost::function<void()> const &>,
                     boost::function<void()>(boost::bind(&io_service::run, &service))));
}

void Server::startAccept() {
    newConnection = boost::make_shared<Connection, io_service &>(service);
    acceptor.async_accept(newConnection->getSocket(), boost::bind(&Server::handleAccept, this, _1));
}

void Server::handleAccept(boost::system::error_code const &error) {
    if(!error) {
        newConnection->start();
    }
    startAccept();
}

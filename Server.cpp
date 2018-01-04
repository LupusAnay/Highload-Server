//
// Created by lupusanay on 27.12.17.
//

#include "Server.h"

Server::Server(unsigned short port, unsigned short thread_count) :
        acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), port)),
        threads(thread_count) {
    // Can use the address already used
    acceptor.set_option(ip::tcp::acceptor::reuse_address(true));
    acceptor.listen();
    startAccept();

    // Fills the thread pool with pointers to threads that execute io_service::run
    generate(threads.begin(), threads.end(),
             boost::bind(
                     &boost::make_shared<boost::thread, boost::function<void()> const &>,
                     boost::function<void()>(boost::bind(&io_service::run, &service))));
}

Server::~Server() {
    for_each(threads.begin(), threads.end(),
                  boost::bind(&io_service::stop, &service));
    for_each(threads.begin(), threads.end(),
                  boost::bind(&boost::thread::join, _1));
}

void Server::handleAccept(const boost::system::error_code &error) {
    if (!error) {
        newConnection->start();
    } else {
        cout << "Error while accepting: " << error.message() << endl;
    }
    startAccept();
}

// Creates a Connection object in the newConnection variable
// and then asynchronously waits for the connection to be received. Uses a handleAccept as a callback
void Server::startAccept() {
    newConnection = boost::make_shared<Connection, io_service &>(service);
    acceptor.async_accept(newConnection->getSocket(),
                          boost::bind(&Server::handleAccept, this, _1));
}


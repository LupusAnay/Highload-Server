//
// Created by lupusanay on 27.12.17.
//

#include "Connection.h"

Connection::Connection(io_service &service) :
        strand(service),
        socket(service) {

}

ip::tcp::socket &Connection::getSocket() {
    return socket;
}

void Connection::start() {
    socket.async_read_some(boost::asio::buffer(buffer),
                           strand.wrap(boost::bind(&Connection::handleRead, shared_from_this(), _1, _2)));
}

void Connection::handleRead(boost::system::error_code const &error, size_t bytes) {
    vector<const_buffer> buffers;
    //http handler calls here
    //Response response = httphanlder(request);
    //const_buffer buffers = buffer(response);
    buffers.emplace_back(buffer.data(), bytes);
    async_write(socket, buffers, strand.wrap(boost::bind(&Connection::handleWrite, shared_from_this(), _1)));
}

void Connection::handleWrite(boost::system::error_code const &error) {
    if (error) {
        return;
    }
    boost::system::error_code code;
    socket.shutdown(ip::tcp::socket::shutdown_both, code);
}

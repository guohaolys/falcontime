/*
    Copyright 2013 Thomas Kent
*/

/************************************************************************ 
This file is part of Falcon Time.

    Falcon Time is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as 
    published by the Free Software Foundation, either version 3 of the 
    License, or (at your option) any later version.

    Falcon Time is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Falcon Time.  If not, see <http://www.gnu.org/licenses/>.
************************************************************************/

#include "TcpConnection.h"
#include "HousekeepingSorter.h"
#include <boost/bind.hpp>
#include <assert.h>

using namespace FalconTime;
using namespace boost::asio::ip;

TcpConnection::TcpConnection(std::string host, unsigned short port, HousekeepingSorter* sorter){
    _sorter = sorter;
    _rcv_buf = new unsigned char[_max_buf_size];
    // _message_size will always point to what the packet says its size will be
    _message_size = reinterpret_cast<unsigned int*>(_rcv_buf); 
    // _message_id will always point to what the packet says its id will be 
    // (after it is actually received and in the buffer)
    _message_id = reinterpret_cast<unsigned int*>(_rcv_buf + 4);

    _server = false;
    _socket = new tcp::socket(_io_service, tcp::v4());
    _host = tcp::endpoint(address_v4::from_string(host), port);

    // Opens a new connection
    _socket->connect(_host);
    this->start_receive();

    _io_thread = new boost::thread(boost::bind(&boost::asio::io_service::run, &_io_service));
}
TcpConnection::TcpConnection(boost::asio::ip::tcp::socket* socket, HousekeepingSorter* sorter){
    _sorter = sorter;
    _rcv_buf = new unsigned char[_max_buf_size];
    _message_size = reinterpret_cast<unsigned int*>(_rcv_buf);
    _message_id = reinterpret_cast<unsigned int*>(_rcv_buf + 4);

    _server = true;
    _socket = socket;
    this->start_receive();
}
TcpConnection::~TcpConnection()
{
    delete [] _rcv_buf;
    if(!_server){
        delete _io_thread;
    }
    delete _socket;
}
void TcpConnection::start_receive(){
    boost::asio::async_read(*_socket, boost::asio::buffer(_rcv_buf,_msg_header_size),  
        boost::bind(&TcpConnection::receive, this, boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}
void TcpConnection::receive(const boost::system::error_code& error, std::size_t bytes){
    if(!error){
        assert(bytes == _msg_header_size); // This is all the space we made available in start_receive
        size_t remaining = *_message_size - _msg_header_size; 
        if(*_message_size < _max_buf_size){
            // read the 'remaining' bytes
            boost::asio::read(*_socket, boost::asio::buffer(_rcv_buf + _msg_header_size,
                remaining));
        }
        // process this message
        _sorter->receive(_rcv_buf, *_message_size);
    }

    // Keep the io service busy with another async_read (this is mandatory)
    this->start_receive();
}
void TcpConnection::send(void* buffer, size_t size){
    _socket->send(boost::asio::buffer(buffer, size));
}
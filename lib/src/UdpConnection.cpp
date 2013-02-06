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
#include "UdpConnection.h"
#include "RealtimeSorter.h"
#include <boost/bind.hpp>

using namespace FalconTime;
using namespace boost::asio::ip;

UdpConnection::UdpConnection(std::string host, unsigned short port, RealtimeSorter* sorter){
    _sorter = sorter;
    _rcv_buf = new unsigned char[_max_buf_size];

    _socket = new udp::socket(_io_service, udp::v4());
    _host = udp::endpoint(address_v4::from_string(host), port);

    _socket->connect(_host);
    this->start_receive();

    _io_thread = new boost::thread(boost::bind(&boost::asio::io_service::run, &_io_service));
}
UdpConnection::~UdpConnection()
{
    delete [] _rcv_buf;
    delete _io_thread;
    delete _socket;
}
void UdpConnection::start_receive(){
    _socket->async_receive_from(boost::asio::buffer(_rcv_buf,_max_buf_size), &_received_from,
        boost::bind(&UdpConnection::receive, this, boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}
void UdpConnection::receive(const boost::system::error_code& error, std::size_t bytes){
    _sorter->receive(_rcv_buf, bytes, _received_from);

    this->start_receive();
}
void UdpConnection::send(void* buffer, size_t size){
    _socket->send(boost::asio::buffer(buffer, size));
}
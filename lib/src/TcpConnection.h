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

#ifndef _TcpConnection_h_
#define _TcpConnection_h_

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <cstddef>
#include <string>

namespace FalconTime{
    class HousekeepingSorter;
    class TcpConnection{
    public:
        TcpConnection(boost::asio::ip::tcp::socket* socket, HousekeepingSorter* sorter);
        TcpConnection(std::string host, unsigned short port, HousekeepingSorter* sorter);
        ~TcpConnection();

        void send(void* message, std::size_t size);
    private:
        HousekeepingSorter* _sorter;
        void start_receive();
        void receive(const boost::system::error_code& error, std::size_t bytes);

        boost::thread* _io_thread;
        boost::asio::io_service _io_service;
        boost::asio::ip::tcp::endpoint _host;
        boost::asio::ip::tcp::socket* _socket;
        static const size_t _max_buf_size = 1048576; //1MB
        unsigned char* _rcv_buf;
        static const size_t _msg_header_size = 8;
        unsigned int* _message_size;
        unsigned int* _message_id;
    };
};
#endif //_TcpConnection_h_
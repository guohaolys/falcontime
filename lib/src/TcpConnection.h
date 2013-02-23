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
    //! A TcpConnection for the low-priority messages
    class TcpConnection{
    public:
        // Use this for server connections that have already been accepted
        TcpConnection(boost::asio::ip::tcp::socket* socket, HousekeepingSorter* sorter);
        // Use this for client connections that need to establish a connection to the server
        TcpConnection(std::string host, unsigned short port, HousekeepingSorter* sorter);
        ~TcpConnection();

        //! Send a message to the server
        void send(void* message, std::size_t size);
    private:
        // Handles the messages after they are successfully received
        HousekeepingSorter* _sorter;
        // Call this after every reply from the async messages, if the _io_service doesn't
        // have one of these it will stop working
        void start_receive();
        // Callback to be registered with the socket
        void receive(const boost::system::error_code& error, std::size_t bytes);

        boost::thread* _io_thread;
        boost::asio::io_service _io_service;
        bool _server;
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
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
#ifndef _Server_h_
#define _Server_h_

#include "base_messages.h"
#include <boost/unordered_map.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace FalconTime{
    class MainClock;
    class ClientConnection;
    class UdpConnection;
    class RealtimeSorter;
    class HousekeepingSorter;

    //! Root of the server process

    //! This will listen for incoming TCP connections (indicating a new client) then 
    //! setup that client allowing for the UdpConnection to receive the time requests.
    class Server{
    public:
        Server(unsigned short port=10320);
        ~Server();

        // Callback to be registered with RealtimeSorter to handle the requests
        void process_time_request(time_request_message m, boost::asio::ip::udp::endpoint from);
    private:
        // Generates the async_accept call for new TCP connections
        void start_accept();
        // When a new TCP connection has been initiated, this sets it up as a 
        // ClientConnection/TcpConnection and sends back the activate_message.
        void handle_accept(boost::asio::ip::tcp::socket* socket, const boost::system::error_code& ec);

        // For making new IDs
        unsigned int get_next_id();
        unsigned int _last_id;

        // All clients that have ever connected
        boost::unordered_map<unsigned int, ClientConnection*> _client_list;

        // Just a clock that keeps track of when started and how much time has passed
        MainClock* _clock;

        // Listens for incoming UDP messages
        UdpConnection* _udp_conn;
        // Sorts the high-performance UDP messages
        RealtimeSorter* _realtime;
        // Sorts the lower-performance TCP messages
        HousekeepingSorter* _housekeeping;

        // Thread and services in the server.
        boost::thread* _io_thread;
        boost::asio::io_service _tcp_service;
        boost::asio::ip::tcp::acceptor _acceptor;
    };
};

#endif //_Server_h_

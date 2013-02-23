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
#include "Server.h"
#include "MainClock.h"
#include "UdpConnection.h"
#include "TcpConnection.h"
#include "RealtimeSorter.h"
#include "HousekeepingSorter.h"
#include "ClientConnection.h"
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace FalconTime;

// The _acceptor is started at instantiation and allows for new TCP connections to 
// be accepted on that port, once the async_accept is registered.
Server::Server(unsigned short port)
    : _acceptor(_tcp_service, boost::asio::ip::tcp::endpoint(
    boost::asio::ip::tcp::v4(), port)){
    // It might be better (more secure too?) if we made the IDs somehow random, but for
    // now we just start here and count up.
    _last_id = 1000;
    _clock = new MainClock();

    _realtime = new RealtimeSorter();
    _realtime->time_request_handler(boost::bind(
        &Server::process_time_request, this, _1, _2));

    _housekeeping = new HousekeepingSorter();

    _udp_conn = new UdpConnection(port, _realtime);

    start_accept();

    _io_thread = new boost::thread(boost::bind(&boost::asio::io_service::run, &_tcp_service));
}

Server::~Server(){
    delete _io_thread;
    //TODO: remove clients from _client_list
    delete _realtime;
    delete _housekeeping;
    delete _udp_conn;
    delete _clock;
}

void Server::process_time_request(time_request_message m, boost::asio::ip::udp::endpoint from){
    time_response_message r;
    r.message_id = TIME_MESSAGE_RESPONSE_ID;
    r.client_id = m.client_id;
    uint64_t ns = _clock->nanoseconds();
    highpref_time t = nanoseconds_to_highpref_time(ns);
    r.seconds = t.seconds;
    r.nanoseconds = t.nanoseconds;

    //TODO/Question - does this happen in the same thread? Should we seperate the 
    // sender/receiver threads for better response (don't wait for the update below)?
    _udp_conn->send(&r, sizeof(time_response_message), from);

    _client_list[m.client_id]->update(ns);
}
void Server::start_accept()
{
    boost::asio::ip::tcp::socket* socket = new boost::asio::ip::tcp::socket(_tcp_service);
    _acceptor.async_accept(*socket, boost::bind(&Server::handle_accept, this, socket, boost::asio::placeholders::error));
}

void Server::handle_accept(boost::asio::ip::tcp::socket* socket, const boost::system::error_code& ec){
    if(!ec)
    {
        unsigned int id = get_next_id();
        TcpConnection* tc = new TcpConnection(socket, _housekeeping);
        ClientConnection* cc = new ClientConnection(tc, id);
        _client_list[id] = cc;

        activate_message m;
        m.message_id = ACTIVATE_MESSAGE_ID;
        m.message_size = ACTIVATE_MESSAGE_SIZE;
        m.client_id = id;
        std::string ts = boost::posix_time::to_simple_string(_clock->start_time_utc());
        if(ts.size() < 100){
            memcpy(&m.time_string, ts.c_str(), ts.size()+1); // Get the /0 at the end of the string
        }

        tc->send(&m, m.message_size);
    }

    this->start_accept();
}

unsigned int Server::get_next_id(){
    _last_id++;
    return _last_id;
}
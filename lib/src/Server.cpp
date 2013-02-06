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

using namespace FalconTime;

Server::Server(unsigned short port){
    _clock = new MainClock();

    _realtime = new RealtimeSorter();
    _realtime->time_request_handler(boost::bind(
        &Server::process_time_request, this, _1, _2));

    _housekeeping = new HousekeepingSorter();
    _housekeeping->startup_message_handler(boost::bind(
        &Server::process_startup_message, this, _1));

    _udp_conn = new UdpConnection(port, _realtime);
}

Server::~Server(){
}

void Server::process_startup_message(startup_message m){

}
void Server::process_time_request(time_request_message m, boost::asio::ip::udp::endpoint from){
    time_response_message r;
    r.message_id = 2;
    r.client_id = m.client_id;
    uint64_t ns = _clock->nanoseconds();
    highpref_time t = nanoseconds_to_highpref_time(ns);
    r.seconds = t.seconds;
    r.nanoseconds = t.nanoseconds;

    _udp_conn->send(&r, sizeof(time_response_message), from);

    _client_list[m.client_id]->update(ns);
}

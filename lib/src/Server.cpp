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
#include <boost/bind.hpp>

using namespace FalconTime;

Server::Server(unsigned short port){
    _clock = new MainClock();

    _realtime = new RealtimeSorter();
    _realtime->time_request_handler(boost::bind(
        &Server::process_time_request, this, _1));

    _housekeeping = new HousekeepingSorter();
    _housekeeping->startup_message_handler(boost::bind(
        &Server::process_startup_message, this, _1));

    _udp_conn = new UdpConnection(port, _realtime);
}

Server::~Server(){
}
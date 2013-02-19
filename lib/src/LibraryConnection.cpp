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

#include "LibraryConnection.h"
#include "SyncedClock.h"
#include "MainClock.h"
#include "Offset.h"
#include "NetworkSyncer.h"
#include "RealtimeSorter.h"
#include "HousekeepingSorter.h"
#include "TcpConnection.h"
#include "UdpConnection.h"
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

using namespace FalconTime;

LibraryConnection::LibraryConnection(SyncedClock* clock)
{
    _offset = clock->get_offset();
    _local_clock = clock->get_local_clock();
}

LibraryConnection::LibraryConnection(SyncedClock* clock, 
            std::string server_address, unsigned int port)
{
    _activated = false;
    _offset = clock->get_offset();
    _local_clock = clock->get_local_clock();

    _network_syncer = new NetworkSyncer(_offset, _local_clock, this);

    _realtime = new RealtimeSorter();
    _realtime->time_response_handler(boost::bind(
        &NetworkSyncer::process_response, _network_syncer, _1));

    _housekeeping = new HousekeepingSorter();
    _housekeeping->offset_update_algorithm_handler(boost::bind(
        &NetworkSyncer::process_algorithm_update, _network_syncer, _1));
    _housekeeping->activate_message_handler(boost::bind(
        &LibraryConnection::process_activate_message, this, _1));

    //Start network services
    _tcp_conn = new TcpConnection(server_address, port, _housekeeping);
    _udp_conn = new UdpConnection(server_address, port, _realtime);

    // Wait untill the callback has received confirmation that its activated.
    boost::posix_time::time_duration timeout = boost::posix_time::millisec(10);
    while(!_activated){
        boost::this_thread::sleep(timeout);
    }
}

void LibraryConnection::process_activate_message(activate_message m){
    std::string start_time = reinterpret_cast<const char*>(m.time_string);
    _offset->set_start(start_time);
    _client_id = m.client_id;
    _activated = true;
}

void LibraryConnection::send_tcp(void* msg, std::size_t size){
    _tcp_conn->send(msg, size);
}
void LibraryConnection::send_udp(void* msg, std::size_t size){
    _udp_conn->send(msg, size);
}
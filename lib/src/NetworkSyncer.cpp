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

#include "NetworkSyncer.h"
#include "HighprefClock.h"
#include "MainClock.h"
#include "Offset.h"

using namespace FalconTime;

NetworkSyncer::NetworkSyncer(Offset* offset, MainClock* local_clock, LibraryConnection* conn){
    _offset = offset;
    _local_clock = local_clock;
    _conn = conn;
    _update_algorithm = RAW_VALUE;
}

void NetworkSyncer::process_response(time_response_message m){
    highpref_time remote_time;
    remote_time.seconds = m.seconds;
    remote_time.nanoseconds = m.nanoseconds;

    uint64_t remote_ns = highpref_time_to_nanoseconds(remote_time);
    uint64_t local_ns = _local_clock->nanoseconds();
    
    // TODO: Add different algorithms to update here
    switch(_update_algorithm){
    case HALF_ROUND_TRIP:
        remote_ns = (remote_ns - _send_time) / 2;
        _offset->set_offset(local_ns - remote_ns)
        break;
    case RAW_VALUE:
    default:
        _offset->set_offset(local_ns - remote_ns);    
    }
    
}
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

#ifndef _NetworkSyncer_h_
#define _NetworkSyncer_h_

#include "base_messages.h"
#include <boost/cstdint.hpp>

namespace FalconTime{
    enum UPDATE_ALGORITHM{
        RAW_VALUE,
        HALF_ROUND_TRIP
    };
    class Offset;
    class MainClock;
    class LibraryConnection;

    class NetworkSyncer{
    public:
        NetworkSyncer(Offset* offset, MainClock* local_clock, LibraryConnection* conn);
        
        void sync();
        void process_response(time_response_message m);

    private:
        Offset* _offset;
        MainClock* _local_clock;
        LibraryConnection* _conn;
        UPDATE_ALGORITHM _update_algorithm;
        uint64_t _send_time;
    };
};

#endif _Syncer_h_

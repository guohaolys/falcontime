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
#ifndef _LibraryConnection_h_
#define _LibraryConnection_h_

#include <string>

namespace FalconTime{
    class SyncedClock;
    class Offset;
    class MainClock;
    class RealtimeSorter;
    class HousekeepingSorter;
    class NetworkSyncer;

    class LibraryConnection{
    public:
        LibraryConnection(SyncedClock* clock);
        LibraryConnection(SyncedClock* clock, 
            std::string server_address, unsigned int port);
        LibraryConnection();

        unsigned get_client_id();

        void send_udp(void* msg, std::size_t size);
        void send_tcp(void* msg, std::size_t size);

    private:
        Offset* _offset;
        MainClock* _local_clock;
        RealtimeSorter* _realtime;
        HousekeepingSorter* _housekeeping;
        NetworkSyncer* _network_syncer;
        unsigned int _client_id;
    };
};
#endif //_LibraryConnection_h_

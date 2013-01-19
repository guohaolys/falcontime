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

#include <boost/unordered_map.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

class ClientConnection;
namespace FalconTime {class HighprefClock;};

class Server{
public:
    Server();
    ~Server();
    void StartServer(unsigned short port);
private:
    boost::unordered_map<unsigned int, ClientConnection*> _client_list;
    FalconTime::HighprefClock* _clock;
    boost::posix_time::ptime _start_time;
};
#endif //_Server_h_
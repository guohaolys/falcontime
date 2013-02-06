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

namespace FalconTime{
    class MainClock;
    class ClientConnection;

    class Server{
    public:
    private:
        boost::unordered_map<unsigned int, ClientConnection*> _client_list;
        MainClock* _clock;
    };
};

#endif //_Server_h_

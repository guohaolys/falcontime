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

#ifndef _ClientConnection_h_
#define _ClientConnection_h_

#include <boost/cstdint.hpp>

namespace FalconTime{
    class TcpConnection;
    class ClientConnection{
    public:
        ClientConnection(TcpConnection* tcp_conn, unsigned int id);

        unsigned int get_id(){return _id;}
    private:
        unsigned int _id;
        TcpConnection* _tcp_conn;
        uint64_t _last_send;
    };
};


#endif // _ClientConnection_h_
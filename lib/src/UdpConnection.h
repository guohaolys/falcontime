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

#ifndef _UdpConnection_h_
#define _UdpConnection_h_

#include <cstddef>
#include <string>

namespace FalconTime{
    class RealtimeSorter;
    class UdpConnection{
    public:
        UdpConnection(std::string host, unsigned short port, RealtimeSorter* sorter);
        ~UdpConnection();

        void send(char*, std::size_t);
    private:
        RealtimeSorter* _sorter;
        void io_loop();

    };
};
#endif //_UdpConnection_h_
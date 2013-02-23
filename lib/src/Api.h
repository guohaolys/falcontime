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

#ifndef _Api_h_
#define _Api_h_

#include "SyncedClock.h"
#include "LibraryConnection.h"
#include "HighprefClock.h"

namespace FalconTime{
    //! This is the behind-the-scenes C++ API used in the client.
    class Api{
    public:
        Api();
        Api(std::string server_address, unsigned short server_port = 10320);
        ~Api();

        //! A string with the starting time in the format YYYY-mmm-DD HH:MM:SS.ffffffffff
        std::string start();
        //! Number of seconds and nanoseconds since start
        highpref_time elapsed();
    private:
        SyncedClock* _clock;
        LibraryConnection* _conn;
    };
};
#endif _Api_h_
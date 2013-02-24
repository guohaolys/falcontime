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

#ifndef _SyncedClock_h_
#define _SyncedClock_h_

#include <boost/cstdint.hpp>

namespace FalconTime{
    class Offset;
    class MainClock;

    class SyncedClock{
    public:
        SyncedClock();
        ~SyncedClock();

        //! Number of nanoseconds since start, including updates from remote 
        
        //! Depending on update algorithm, this could be monotonic
        uint64_t nanoseconds();

        Offset* get_offset(){return _offset;}
        MainClock* get_local_clock(){return _local_clock;}

    private:
        MainClock* _local_clock;
        Offset* _offset;
    };
};

#endif //_SyncedClock_h_
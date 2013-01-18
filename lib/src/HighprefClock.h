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
#ifndef _HighprefClock_h
#define _HighprefClock_h

#include <boost/cstdint.hpp>
#include <string>

namespace FalconTime{
    class HighprefClock{
    public:
        HighprefClock();
        uint64_t nanoseconds(){
            return local_nanoseconds() - _local_start_offset;
        }

    private:
        uint64_t local_nanoseconds();
        uint64_t _local_start_offset;
    };
};
#endif //_HighprefClock_h

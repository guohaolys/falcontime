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

#ifndef _MainClock_h_
#define _MainClock_h_

#define BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG

#include "HighprefClock.h"
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/cstdint.hpp>

namespace FalconTime{
    //! A basic clock that works with the HighprefClock to add on utc.
    class MainClock{
    public:
        MainClock();
        ~MainClock();

        //! Current time in UTC
        boost::posix_time::ptime utc_time();
        //! Nanoseconds since started
        uint64_t nanoseconds() {return _local_clock->nanoseconds();}
        //! Time started in UTC
        boost::posix_time::ptime start_time_utc() {return _start_time;}
    private:
        FalconTime::HighprefClock* _local_clock;
        boost::posix_time::ptime _start_time;
    };
};
#endif _MainClock_h_
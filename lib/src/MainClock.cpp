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

#include "MainClock.h"
#include "HighprefClock.h"
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace FalconTime;

MainClock::MainClock(){
    _local_clock = new FalconTime::HighprefClock();
    _start_time = boost::posix_time::microsec_clock::universal_time();
}

MainClock::~MainClock(){
    delete _local_clock;
}

boost::posix_time::ptime MainClock::utc_time(){
    using namespace boost::posix_time;

    highpref_time elapsed = nanoseconds_to_highpref_time(this->nanoseconds());
    time_duration elapsed_duration = seconds(elapsed.seconds) + boost::posix_time::nanoseconds(elapsed.nanoseconds);
    return _start_time + elapsed_duration;
}
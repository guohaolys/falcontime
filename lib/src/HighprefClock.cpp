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

#include "HighprefClock.h"

#ifdef WIN32
  #include <windows.h>
#else
  #include <time.h>
#endif

using namespace FalconTime;

HighprefClock::HighprefClock(){
    _local_start_offset = this->local_nanoseconds();
}

uint64_t HighprefClock::local_nanoseconds(){
#ifdef WIN32
    LARGE_INTEGER frequency;
    LARGE_INTEGER measurement;

    QueryPerformanceCounter(&measurement);
    QueryPerformanceFrequency(&frequency);

    return (measurement.QuadPart * 1000000000) / frequency.QuadPart;
#else
    timespec tp;
    clock_gettime(CLOCK_REALTIME, &tp);
    return static_cast<uint64_t>((tp.tv_sec * NSEC_PER_SEC) + tp.tv_nsec);
#endif
}
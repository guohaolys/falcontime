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

#include "SyncedClock.h"
#include "Offset.h"
#include "MainClock.h"

using namespace FalconTime;

SyncedClock::SyncedClock(){
    _local_clock = new MainClock();
    _offset = new Offset();
}

SyncedClock::~SyncedClock(){
    delete _local_clock;
    delete _offset;
}

uint64_t SyncedClock::nanoseconds(){
    return _local_clock->nanoseconds() - _offset->get_offset();
}
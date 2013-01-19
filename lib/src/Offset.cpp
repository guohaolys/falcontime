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

#include "Offset.h"

using namespace FalconTime;

// TODO: This is not thread-safe and should be! We need to add mutexes or
// fancy ways of flushing cache between reads and writes.

void Offset::set_offset(int64_t value){
    _offset = value;
}
void Offset::set_start(std::string value){
    _start = value;
}

int64_t Offset::get_offset(){
    return _offset;
}
std::string Offset::get_start(){
    return _start;
}
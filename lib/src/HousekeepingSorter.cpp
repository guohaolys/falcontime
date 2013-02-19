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

#include "HousekeepingSorter.h"
#include <boost/foreach.hpp>
#include <assert.h>

using namespace FalconTime;

void HousekeepingSorter::receive(void* buffer, size_t buffer_length){
    assert(buffer_length >= 8);
    unsigned int* int_buffer = reinterpret_cast<unsigned int*>(buffer); 
    unsigned char* char_buffer = reinterpret_cast<unsigned char*>(buffer);
    unsigned int length = int_buffer[0];
    assert(length == buffer_length);
    unsigned int message_id = int_buffer[1];

    switch(message_id){
    case 51:
        this->activate(char_buffer, buffer_length);
        break;
    case 52:
        this->timezone(char_buffer, buffer_length);
        break;
    case 53:
        this->offset_algorithm(char_buffer, buffer_length);
        break;
    default:
        break;
    }
}
void HousekeepingSorter::activate(unsigned char* buffer, unsigned int buffer_length){
    assert(buffer_length == 108);
    activate_message* m = reinterpret_cast<activate_message*>(buffer);
    BOOST_FOREACH(boost::function<void (activate_message)> handler, _activate_handlers){
        handler(*m);
    }
}
void HousekeepingSorter::timezone(unsigned char* buffer, unsigned int buffer_length){
    assert(buffer_length == 12);
    timezone_offset* m = reinterpret_cast<timezone_offset*>(buffer);
    BOOST_FOREACH(boost::function<void (timezone_offset)> handler, _timezone_handlers){
        handler(*m);
    }
}
void HousekeepingSorter::offset_algorithm(unsigned char* buffer, unsigned int buffer_length){
    assert(buffer_length == 116);
    offset_update_algorithm* m = reinterpret_cast<offset_update_algorithm*>(buffer);
    BOOST_FOREACH(boost::function<void (offset_update_algorithm)> handler, _offset_algorithm_handlers){
        handler(*m);
    }
}

void HousekeepingSorter::activate_message_handler(boost::function<void (activate_message)> handler){
    _activate_handlers.push_back(handler);
}
void HousekeepingSorter::timezone_offset_handler(boost::function<void (timezone_offset)> handler){
    _timezone_handlers.push_back(handler);
}
void HousekeepingSorter::offset_update_algorithm_handler(boost::function<void (offset_update_algorithm)> handler){
    _offset_algorithm_handlers.push_back(handler);
}
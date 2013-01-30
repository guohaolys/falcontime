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

#include "RealtimeSorter.h"
#include <boost/foreach.hpp>
#include <assert.h>

using namespace FalconTime;

void RealtimeSorter::receive(void* buffer, size_t buffer_length){
    assert(buffer_length >= 4);
    unsigned int* int_buffer = reinterpret_cast<unsigned int*>(buffer); 
    unsigned char* char_buffer = reinterpret_cast<unsigned char*>(buffer);
    unsigned int message_id = int_buffer[0];

    switch(message_id){
    case 1:
        this->request(char_buffer, buffer_length);
        break;
    case 2:
        this->response(char_buffer, buffer_length);
        break;
    default:
        break;
    }
}

void RealtimeSorter::request(unsigned char* buffer, unsigned int buffer_length){
    assert(buffer_length == 8);
    time_request_message* m = reinterpret_cast<time_request_message*>(buffer);
    BOOST_FOREACH(boost::function<void (time_request_message)> handler, _request_handlers){
        handler(*m);
    }
}

void RealtimeSorter::response(unsigned char* buffer, unsigned int buffer_length){
    assert(buffer_length == 16);
    time_response_message* m = reinterpret_cast<time_response_message*>(buffer);
    BOOST_FOREACH(boost::function<void (time_response_message)> handler, _response_handlers){
        handler(*m);
    }
}

void RealtimeSorter::time_request_handler(boost::function<void (time_request_message)> handler){
    _request_handlers.push_back(handler);
}
void RealtimeSorter::time_response_handler(boost::function<void (time_response_message)> handler){
    _response_handlers.push_back(handler);
}

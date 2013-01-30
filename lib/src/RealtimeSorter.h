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

#ifndef _RealtimeSorter_h_
#define _RealtimeSorter_h_

#include "base_messages.h"
#include <boost/function.hpp>
#include <list>

namespace FalconTime{

    class RealtimeSorter{
    public:
        void receive(void* buffer, size_t buffer_length);
    
        void time_request_handler(boost::function<void (time_request_message)> handler);
        void time_response_handler(boost::function<void (time_response_message)> handler);
    private:
        void request(unsigned char* buffer, unsigned int buffer_length);
        void response(unsigned char* buffer, unsigned int buffer_length);

        std::list<boost::function<void (time_request_message)> > _request_handlers;
        std::list<boost::function<void (time_response_message)> > _response_handlers;
    };
};
#endif // _RealtimeSorter_h_
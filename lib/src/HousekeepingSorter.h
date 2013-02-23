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

#ifndef _HousekeepingSorter_h_
#define _HousekeepingSorter_h_

#include "base_messages.h"
#include <boost/function.hpp>
#include <list>

namespace FalconTime{
    //! Sorts messages that come over the low-priority TCP connection
    class HousekeepingSorter{
    public:
        // Register this callback with the TCP connection
        void receive(void* buffer, size_t buffer_length);

        //! Register a callback to be called when a activate_message comes in
        void activate_message_handler(boost::function<void (activate_message)> handler);
        //! Register a callback to be called when a timezone offset message comes in
        void timezone_offset_handler(boost::function<void (timezone_offset)> handler);
        //! Register a callback to be called when an offset update algorithm message comes in
        void offset_update_algorithm_handler(boost::function<void (offset_update_algorithm)> handler);

    private:
        // These are where the processing happens
        void startup(unsigned char* buffer, unsigned int buffer_length);
        void activate(unsigned char* buffer, unsigned int buffer_length);
        void timezone(unsigned char* buffer, unsigned int buffer_length);
        void offset_algorithm(unsigned char* buffer, unsigned int buffer_length);

        // Lists of the callbacks that need to be called for each message
        std::list<boost::function<void (activate_message)> > _activate_handlers;      
        std::list<boost::function<void (timezone_offset)> > _timezone_handlers;
        std::list<boost::function<void (offset_update_algorithm)> > _offset_algorithm_handlers;      
    };
};
#endif // _HousekeepingSorter_h_
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
#include <boost/asio/ip/udp.hpp>
#include <list>

namespace FalconTime{
    //! Sorts messages that come over the low-latency UDP connection
    class RealtimeSorter{
    public:
        // Register this callback with the UDP connection
        void receive(void* buffer, size_t buffer_length, boost::asio::ip::udp::endpoint from);
    
        //! Register a callback to be called when a time_request message comes in
        void time_request_handler(boost::function<void (time_request_message, boost::asio::ip::udp::endpoint)> handler);
        //! Register a callback to be called when a time_response message comes in
        void time_response_handler(boost::function<void (time_response_message)> handler);
    private:
        // These are where the processing happens
        void request(unsigned char* buffer, unsigned int buffer_length, boost::asio::ip::udp::endpoint from);
        void response(unsigned char* buffer, unsigned int buffer_length);

        // Lists of the callbacks that need to be called for each message
        std::list<boost::function<void (time_request_message, boost::asio::ip::udp::endpoint)> > _request_handlers;
        std::list<boost::function<void (time_response_message)> > _response_handlers;
    };
};
#endif // _RealtimeSorter_h_
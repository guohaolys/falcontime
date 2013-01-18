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

#ifndef _base_messages_h_
#define _base_messages_h_

struct time_request_message{
    unsigned int message_id; /* 1 */
    unsigned int client_id; /* Client's GUID */
}

struct time_response_message{
    unsigned int message_id; /* 2 */
    unsigned int client_id;
    unsigned int seconds; /* Since start of server program */
    unsigned int nanoseconds; /* Since last second rollover */
}

struct startup_message{
    unsigned int message_size; /* 12 */
    unsigned int message_id; /* 50 */
    unsigned int client_id; /* Generated GUID */
}

struct activate_message{
    unsigned int message_size; /* 108 */
    unsigned int message_id; /* 51 */
    /* time of zero seconds, format: "YYYY-MM-DD HH:MM:SS.DDDDDDDDDDDDDDDDDDDDDDD" 
       null terminated, UTC value */
    unsigned char[100] time_string; 
}

struct timezone_offset{
    unsigned int message_size; /* 12 */
    unsigned int message_id; /* 52 */
    /* number of seconds offset from UTC, usually a multiple of 3600 (1hr) or 
       1800 (30min) */
    int offset_seconds;
}

#endif /*_base_messages_h*/

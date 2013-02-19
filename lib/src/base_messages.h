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

#define TIME_MESSAGE_REQUEST_ID 1
#define TIME_MESSAGE_RESPONSE_ID 2
#define STARTUP_MESSAGE_ID 50
#define ACTIVATE_MESSAGE_ID 51
#define TIMEZONE_OFFSET_ID 52

struct time_request_message{
    unsigned int message_id; /* 1 */
    unsigned int client_id; /* Client's GUID */
};

struct time_response_message{
    unsigned int message_id; /* 2 */
    unsigned int client_id;
    unsigned int seconds; /* Since start of server program */
    unsigned int nanoseconds; /* Since last second rollover */
};

struct activate_message{
    unsigned int message_size; /* 112 */
    unsigned int message_id; /* 51 */
    unsigned int client_id; /* Generated GUID */
    /* time of zero seconds, format: "YYYY-MM-DD HH:MM:SS.DDDDDDDDDDDDDDDDDDDDDDD" 
       null terminated, UTC value */
    unsigned char time_string[100]; 
};

struct timezone_offset{
    unsigned int message_size; /* 12 */
    unsigned int message_id; /* 52 */
    /* number of seconds offset from UTC, usually a multiple of 3600 (1hr) or 
       1800 (30min) */
    int offset_seconds;
};

struct offset_update_algorithm{
    unsigned int message_size; /* 116 */
    unsigned int message_id; /* 53 */
    unsigned char algorithm[100];
    unsigned int ignore_below;
    unsigned int rate;
};
#endif /*_base_messages_h*/

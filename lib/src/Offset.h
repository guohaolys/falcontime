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

#ifndef _Offset_h_
#define _Offset_h_

#include <boost/cstdint.hpp>
#include <string>

namespace FalconTime{
    class Offset{
    public:
        Offset();
        ~Offset();

        int64_t get_offset();
        std::string get_start();

        void set_offset(int64_t value);
        void set_start(std::string);
    private:
        // Number of nanoseconds the local clock is off from the main clock
        int64_t _offset; 
        // This is the start of the main clock, nothing local.
        std::string _start; 
    };
};

#endif //_Offset_h_

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

#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int falcon_main(int argc, char* argv[])
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
		("server", "run as server not client (client is default)")
		("port", "change port from the default of 10320")
    ;

    po::variables_map vm;        
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);    

	bool server = false;
	unsigned short port = 10320;

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

	if (vm.count("server")) {
		server = true;
	}
	if (vm.count("port")) {
		port = vm["port"].as<unsigned short>();
	}
    return 0;
}

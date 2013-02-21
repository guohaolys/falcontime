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

#include "Server.h"
#include "HighprefClock.h"
#include "falcontime.h"
#include <boost/program_options.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <string>

using namespace FalconTime;
namespace po = boost::program_options;

int falcon_main(int argc, char* argv[])
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("client", po::value<std::string>(), "run as client to this IP (of server) (by default runs as server)")
        ("port", po::value<unsigned short>(), "change port from the default of 10320")
    ;

    po::variables_map vm;        
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);    

    bool server = true;
    std::string server_address;
    unsigned short port = 10320;

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    if (vm.count("client")) {
        server = false;
        server_address = vm["client"].as<std::string>();
    }
    if (vm.count("port")) {
        port = vm["port"].as<unsigned short>();
    }

    if(server){
        Server* s = new Server(port);
        std::cout << "Service started on port: " << port << std::endl;
        while(true){
            boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
        }
        
    }else{
        if(enable_falcon_time_as_client(server_address.c_str(), port) == 0){
            char start[100];
            get_start(start);
            std::cout << "Start time: " << start << std::endl;

            HighprefClock* c = new HighprefClock();
            uint64_t local_ns;
            uint64_t test_ns;
            int step = 0;

            while(true){
                local_ns = c->nanoseconds();
                highpref_time t = get_time();
                test_ns = highpref_time_to_nanoseconds(t);
                int64_t diff_ns = local_ns - test_ns;
                std::cout << "at step " << step << " local: " << local_ns << " test: " << test_ns << " difference: " << diff_ns << std::endl;
                step++;
                boost::this_thread::sleep_for(boost::chrono::milliseconds(3000));
            }
        }
    }
    return 0;
}

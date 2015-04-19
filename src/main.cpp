/*
 * main.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: dmitry
 */

#include "Server.h"

int main(int argc, char **argv) {
//	std::cout << "base: " << getpid() << std::endl;
//	switch (fork()) {
//	case 0: // child
//		std::cout << "children: " << getpid() << std::endl;
//		break;
//	case -1: // error
//		break;
//	default: //parent
//		std::cout << "parent: " << getpid() << std::endl;
//	}

	Server server = Server();
	server.init();
	server.bind_s(8080);
	server.run();
}


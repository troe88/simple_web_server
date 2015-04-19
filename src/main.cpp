/*
 * main.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: dmitry
 */

#include "Server.h"

int main(int argc, char **argv) {
	Server server = Server();
	server.init();
	server.bind_s(8080);
	server.run();
}




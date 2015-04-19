/*
 * Server.h
 *
 *  Created on: Apr 19, 2015
 *      Author: dmitry
 */

#ifndef SERVER_H_
#define SERVER_H_
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include "parser.h"
#include <unistd.h>

#define BUF_SIZE 1024
#define SERVER_FOLDER "/home/dmitry/Documents/c_plusplus_Worspace/EclipseProject/web_server/server_folder"
#define PAGE_404 "/home/dmitry/Documents/c_plusplus_Worspace/EclipseProject/web_server/server_folder/errors/404.html"

class Server {
private:
	int _socket;
	int _client_fd;
	struct sockaddr_in _cli_addr;
	socklen_t _sin_len;
	char *buf;
	Parser _parser;

private:
	const std::string recv_s();
	void send(const std::string &path);
	void whatToDo();
	void close_s() { close(_client_fd); }
	const std::string genHeader(uint16_t code, const std::string& msg);
	bool isConnected();

public:
	Server();
	void init();
	void bind_s(const int port);
	void run();

	virtual ~Server();
};

#endif /* SERVER_H_ */

/*
 * Server.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: dmitry
 */

#include "Server.h"
#include <iostream>
#include <fstream>
#include "helper.h"

using std::cout;
using std::endl;
using std::cerr;

Server::Server() {
#ifndef DAEMON_MODE
	cout << "Server()" << endl;
#endif
	_socket = 0;
	_sin_len = sizeof(_cli_addr);
	buf = new char[BUF_SIZE];
	_client_fd = 0;
	_parser = Parser();
}

void Server::init() {
#ifndef DAEMON_MODE
	cout << "init()" << endl;
#endif
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == -1) {
		srv_print(MakeString() << "init(): " << strerror(errno), LOG_ERR);
		exit(-1);
	}

	int optval = 1;
	if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int))
			== -1) {
		srv_print(MakeString() << "init(): " << strerror(errno), LOG_ERR);
		exit(-1);
	}

}

void Server::bind_s(const int port) {
#ifndef DAEMON_MODE
	cout << "bind()" << endl;
#endif
	struct sockaddr_in svr_addr;
	svr_addr.sin_family = AF_INET;
	svr_addr.sin_addr.s_addr = INADDR_ANY;
	svr_addr.sin_port = htons(port);

	if (bind(_socket, (struct sockaddr *) &svr_addr, sizeof(svr_addr)) == -1) {
		close(_socket);
		srv_print(MakeString() << "bind(): " << strerror(errno), LOG_ERR);
	}
}

void Server::run() {
//	cout << "run()" << endl;
#ifndef DAEMON_MODE
	cout << "run()" << endl;
#endif
	listen(_socket, 1);
	while (true) {
		if (isConnected()) {
			switch (fork()) {
			case 0: // child
				_parser.set(recv_s());
				whatToDo();
				close_s();
				break;
			case -1: // error
				srv_print(MakeString() << "recv_s(): " << strerror(errno),
						LOG_ERR);
				break;
			default: //parent
				close_s();
			}
		}
	}
}

bool Server::isConnected() {
	_client_fd = accept(_socket, (struct sockaddr *) &_cli_addr, &_sin_len);
	if (_client_fd == -1) {
		srv_print(MakeString() << "isConnected(): " << strerror(errno),
				LOG_ERR);
		return false;
	}
	return true;
}

void Server::whatToDo() {
	switch (_parser.getMethod()) {
	case GET:
		send(_parser.getPage());
		break;
	case POST:
		break;
	case HEAD:
		break;
	case EMPTY:
	default:
		srv_print(MakeString() << "This method does not supported\n", LOG_ERR);
		break;
	}
}

const std::string Server::genHeader(uint16_t code, const std::string& msg) {
	std::stringstream stream;
	stream << "HTTP/1.1" << code << msg << endl;
	stream << "Content-Type: text/html; charset=UTF-8" << endl << endl;
	return stream.str();
}

void Server::send(const std::string &path) {
	std::stringstream stream;
	std::string abs_path = SERVER_FOLDER + path;

	if (access(SERVER_FOLDER, F_OK) != -1) {
		if (access(abs_path.c_str(), F_OK) != -1) {
			stream << genHeader(200, "OK");
			stream << dataFromFile(abs_path);
		} else {
			stream << genHeader(404, "Page not found");
			stream << dataFromFile(PAGE_404);
		}
	} else {
		stream << genHeader(404, "Server directory not found");
		stream << "<!DOCTYPE html><html><body><h1>server folder not found</h1></body></html>";
		srv_print(MakeString() << "server_folder not found", LOG_ERR);
	}

	write(_client_fd, stream.str().c_str(), stream.str().size());
}

const std::string Server::recv_s() {
#ifndef DAEMON_MODE
	cout << "connected..." << endl;
#endif
	int bytes_read = recv(_client_fd, &*buf, BUF_SIZE, 0);
	if (bytes_read == -1) {
		srv_print(MakeString() << "recv_s(): " << strerror(errno), LOG_ERR);
		return NULL;
	}

	return std::string(buf, bytes_read);
}

Server::~Server() {
	delete buf;
}


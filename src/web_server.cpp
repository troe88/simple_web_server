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
#include "Server.h"

char response[] = "HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html; charset=UTF-8\r\n\r\n"
		"<!DOCTYPE html><html><head><title>Simple page</title></head>"
		"<body><h1>Simple WEB server, it's not apache2.</h1>"
		"</body></html>\r\n";

int main1() {
	int one = 1, client_fd;
	struct sockaddr_in svr_addr, cli_addr;
	socklen_t sin_len = sizeof(cli_addr);

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		err(1, "can't open socket");

	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));

	int port = 8080;
	svr_addr.sin_family = AF_INET;
	svr_addr.sin_addr.s_addr = INADDR_ANY;
	svr_addr.sin_port = htons(port);

	if (bind(sock, (struct sockaddr *) &svr_addr, sizeof(svr_addr)) == -1) {
		close(sock);
		err(1, "Can't bind");
	}

	const int buf_size = 1024;
	char buf[buf_size];
	Parser parser = Parser();

	listen(sock, 1);
	while (true) {
		client_fd = accept(sock, (struct sockaddr *) &cli_addr, &sin_len);

		std::cout << "connected..." << std::endl;

		if (client_fd == -1) {
			printf("%s\n", strerror(errno));
			continue;
		}
		int bytes_read = recv(client_fd, buf, buf_size, 0);

		if (bytes_read == -1) {
			printf("%s\n", strerror(errno));
			continue;
		}

		parser.set(buf, bytes_read);

		switch (parser.getMethod()) {
		case GET:
			write(client_fd, response, sizeof(response) - 1);
			break;
		case POST:
			break;
		case HEAD:
			break;
		case EMPTY:
		default:
			std::cout << "This method does not supported" << std::endl;
			break;
		}

		close(client_fd);
	}
}

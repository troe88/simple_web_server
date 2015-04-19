/*
 * main.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: dmitry
 */

#include "Server.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <syslog.h>
#include "helper.h"

void signal_handler(int sig) {
	switch (sig) {
	case SIGHUP:
		syslog(LOG_INFO, "Reload conf file\n");
		break;
	case SIGTERM:
		syslog(LOG_INFO, "Close daemon...\n");
		exit(0);
		break;
	}
}

int main(int argc, char **argv) {
#ifdef DAEMON_MODE
	int pid = fork();

	switch (pid) {
	case 0: // child
	{

		umask(0);
		setsid();

		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);

		signal(SIGHUP, signal_handler);
		signal(SIGTERM, signal_handler);
		openlog("web_server", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
		srv_print(MakeString() << "start!", LOG_INFO);
#endif
		Server server = Server();
		server.init();
		server.bind_s(8080);
		server.run();
#ifdef DAEMON_MODE
		break;
	}
	case -1: // error!
	default: // parent
		return 0;
	}
#endif
}


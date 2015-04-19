/*
 * helper.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: dmitry
 */

#include "helper.h"

std::vector<std::string> &split(const std::string &s, char delim,
		std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

const std::string dataFromFile(const std::string &path) {
	std::string line;
	std::stringstream stream;
	std::ifstream myfile(path.c_str());
	while (std::getline(myfile, line)) {
		stream << line;
	}

	myfile.close();

	return stream.str();
}

void srv_print(const std::string &str, int type) {

#ifdef DAEMON_MODE
	syslog(type, str.c_str());
#else
	switch (type) {
	case LOG_ERR:
		std::cerr << str;
		break;
	case LOG_INFO:
	default:
		std::cout << str;
		break;
	}
#endif

}

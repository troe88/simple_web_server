/*
 * helper.h
 *
 *  Created on: Apr 19, 2015
 *      Author: dmitry
 */

#ifndef HELPER_H_
#define HELPER_H_

#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <syslog.h>

#define DAEMON_MODE

class MakeString {
public:
	template<class T>
	MakeString& operator<<(const T& arg) {
		m_stream << arg;
		return *this;
	}
	operator std::string() const {
		return m_stream.str();
	}
protected:
	std::stringstream m_stream;
};

std::vector<std::string> &split(const std::string &s, char delim,
		std::vector<std::string> &elems);

std::vector<std::string> split(const std::string &s, char delim);

const std::string dataFromFile(const std::string &path);

void srv_print(const std::string &str, int type);

#endif /* HELPER_H_ */

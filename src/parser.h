/*
 * parser.h
 *
 *  Created on: Apr 19, 2015
 *      Author: dmitry
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <stdint.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>


enum {
	EMPTY, GET, POST, HEAD
};

class Parser {

	uint16_t _method;
	std::string _page;

public:
	const int getMethod() { return _method; }
	const std::string& getPage() { return _page; }

	void set(const char* data, int size);
	void set(const std::string &str);
	Parser();
	virtual ~Parser();
};

#endif /* PARSER_H_ */

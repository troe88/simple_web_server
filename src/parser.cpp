/*
 * parser.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: dmitry
 */

#include "parser.h"
#include "helper.h"
using namespace std;

Parser::Parser() {
	_method = EMPTY;
	_page = "/index.html";
}

void Parser::set(const string &str) {
	set(str.c_str(), str.length());
}

void Parser::set(const char* data, int size) {
	stringstream stream(data);
	string line;
	vector<string> msg;

	while (getline(stream, line, '\n')) {
		msg.push_back(line);
	}

	vector<string> first = split(msg[0], ' ');

	if (first[0] == "GET") {
		_method = GET;
	} else if (first[0] == "POST") {
		_method = POST;
	} else if (first[0] == "HEAD") {
		_method = HEAD;
	} else {
		_method = EMPTY;
	}

	if (first[1] == "/")
		return;
	_page = first[1];

}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}


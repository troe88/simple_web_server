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

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

std::vector<std::string> split(const std::string &s, char delim);

const std::string dataFromFile(const std::string &path);

#endif /* HELPER_H_ */

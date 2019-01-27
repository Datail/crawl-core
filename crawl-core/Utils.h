#pragma once

#ifndef __UTILS_H
#define __UTILS_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>


#ifdef _WIN32

#include <WinSock2.h>
#include <WS2tcpip.h> 

static WSADATA g_wsa_data;

#endif

class Utils
{
public:
	Utils();
	~Utils();

	std::vector<std::string> Split(std::string s, char token);
	char net_init(void);
	void net_deinit(void);
};

#endif
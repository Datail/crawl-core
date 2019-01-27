#pragma once

#ifndef __RESOLVER_H
#define __RESOLVER_H

#include <string>


#ifndef _WIN32

#include <sys/socket.h> 
#include <netdb.h>

#endif


#include "Utils.h"
#include "Url.h"

class Resolver
{
public:
	Resolver();
	~Resolver();
	std::string Resolve(Url url); // returns URL's hostname's IP
private:
	Utils misc;
};

#endif
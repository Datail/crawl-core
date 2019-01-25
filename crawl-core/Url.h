#pragma once

#ifndef __URL_H
#define __URL_H

#include <string>


using namespace std;


class Url
{
public:
	Url(string);
	~Url();

	size_t UniqueId;
	string Value;
	bool AlreadyDownloaded;
};


#endif
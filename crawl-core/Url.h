#pragma once

#ifndef __URL_H
#define __URL_H

#include <string>


class Url
{
public:
	Url(std::string);
	~Url();

	size_t UniqueId;
	std::string Value;
	bool AlreadyDownloaded;
};


#endif
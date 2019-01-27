#pragma once

#ifndef __FRONTIER_H
#define __FRONTIER_H

#include <queue>
#include <list>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

#include "Main.h"
#include "Url.h"
#include "Resolver.h"

class Frontier
{
public:
	Frontier();
	~Frontier();

	void Fill(std::vector<std::string> seeds, int);
	void RegisterUrl(Url);
	void ArchiveUrl(size_t);
	void AssignUrl(Resolver *);
	Url GetUrl();
	std::queue<Url> GetUrlQueue(std::string);
	std::vector<std::string> GetQueuesKeys();
	bool IsEmpty();

private:
	std::map<std::string, std::queue<Url>> _internal_urls_per_host;
	std::queue<Url> _internal_fifo_struct;
	std::list<size_t> _internal_downloaded_urls;
	std::list<size_t>::iterator _it;

};

#endif

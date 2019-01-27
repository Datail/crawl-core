#pragma once

#ifndef __FRONTIER_H
#define __FRONTIER_H

#include <queue>
#include <list>
#include <string>
#include <algorithm>
#include <vector>

#include "Main.h"
#include "Url.h"


class Frontier
{
public:
	Frontier();
	~Frontier();

	void Fill(std::vector<std::string> seeds, int);
	void RegisterUrl(Url);
	void ArchiveUrl(size_t);
	Url GetUrl();
	bool IsEmpty();

private:
	std::queue<Url> _internal_fifo_struct;
	std::list<size_t> _internal_downloaded_urls;
	std::list<size_t>::iterator _it;
};

#endif

#pragma once

#ifndef __FRONTIER_H
#define __FRONTIER_H

#include <queue>
#include <list>
#include <algorithm>

#include "Main.h"
#include "Url.h"

using namespace std;

class Frontier
{
public:
	Frontier();
	~Frontier();

	void Fill(vector<string> seeds, int);
	void RegisterUrl(Url);
	void ArchiveUrl(size_t);
	Url GetUrl();
	bool IsEmpty();

private:
	queue<Url> _internal_fifo_struct;
	list<size_t> _internal_downloaded_urls;
	std::list<size_t>::iterator _it;
};

#endif

#pragma once

#ifndef __FRONTIER_H
#define __FRONTIER_H

#include <queue>
#include "Main.h"

using namespace std;

class Frontier
{
public:
	Frontier();
	~Frontier();

	void Fill(vector<string> seeds, int);
	void RegisterUrl(string);
	string GetUrl();
	bool IsEmpty();

private:
	queue<string> _internal_fifo_struct;
};

#endif

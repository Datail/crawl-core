#pragma once

#ifndef __FETCHER_H
#define __FETCHER_H


#include <thread>
#include "Frontier.h"

using namespace std;

class Fetcher
{
public:
	Fetcher(vector<string> seeds, int nseeds);
	~Fetcher();

	Frontier FrontierURLs;

	void Run();
};


#endif
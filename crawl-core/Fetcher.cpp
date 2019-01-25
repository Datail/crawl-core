#include "Fetcher.h"



Fetcher::Fetcher(vector<string> seeds, int nseed)
{
	FrontierURLs.Fill(seeds, nseed);
}


Fetcher::~Fetcher()
{
}


void Fetcher::Run()
{
	do {
		auto f = [](Fetcher* executer) {
			executer->FrontierURLs.GetUrl(); /// Get URL from Frontier repository
			/// Resolve DNS via DNS servers
			/// Use resolved IP address to download HTML pages
			/// Extract links/URLs from within HTML pages
			/// Validate URLs, assign a weight to each URL object, discard unrelevant URLs
			/// Push extracted and validated URLs to Frontier
		};

		thread main_thread(f, this);

		/// Wait for main thread to finish
		main_thread.join();
	} while (!FrontierURLs.IsEmpty());
}
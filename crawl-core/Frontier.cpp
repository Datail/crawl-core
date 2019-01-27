#include "Frontier.h"

using namespace std;

Frontier::Frontier()
{
	_it = _internal_downloaded_urls.begin();
}


Frontier::~Frontier()
{
}


void Frontier::Fill(vector<string> urls, int max_urls)
{
	for (int i = 0; i < max_urls; i++) {
		_internal_fifo_struct.push(Url(urls[i]));
	}
}


void Frontier::RegisterUrl(Url s) 
{
	_it = find(_internal_downloaded_urls.begin(), _internal_downloaded_urls.end(), s.UniqueId);
	if(_it == _internal_downloaded_urls.end())   // Only add URL to frontier repo if it hasn't been crawled yet
		_internal_fifo_struct.push(s);	
}


void Frontier::ArchiveUrl(size_t url_hash)
{
	_internal_downloaded_urls.push_back(url_hash);
}

Url Frontier::GetUrl()
{
	Url url = _internal_fifo_struct.front();
	if(!_internal_fifo_struct.empty())
		_internal_fifo_struct.pop();
	return url;
}


bool Frontier::IsEmpty()
{
	return _internal_fifo_struct.empty();
}
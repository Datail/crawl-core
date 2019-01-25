#include "Frontier.h"


Frontier::Frontier()
{
	
}


Frontier::~Frontier()
{
}


void Frontier::Fill(vector<string> urls, int max_urls)
{
	for (int i = 0; i < max_urls; i++) {
		_internal_fifo_struct.push(urls[i]);
	}
}


void Frontier::RegisterUrl(string s) 
{
	_internal_fifo_struct.push(s);	
}

string Frontier::GetUrl()
{
	string url = _internal_fifo_struct.front();
	_internal_fifo_struct.pop();
	return url;
}


bool Frontier::IsEmpty()
{
	return _internal_fifo_struct.empty();
}
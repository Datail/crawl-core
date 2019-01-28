#include "Poco/Exception.h"
#include "Frontier.h"

#include <mutex>

using namespace std;
using Poco::Exception;

Frontier::Frontier()
{
	_it = _internal_downloaded_urls.begin();
}


Frontier::~Frontier()
{
}

void Frontier::AssignUrl(Resolver *dnsResolver)
{
	Url url = GetUrl();
	string host = dnsResolver->Resolve(url);
	

	queue<Url> queueUrl;
	
	unique_lock<mutex> mlock(mutex_multi_); // mutex scope lock
	while (_internal_urls_per_host.empty()) // check condition to be safe against spurious wakes
	{
		cond_multi_.wait(mlock); // release lock and go join the waiting thread queue
	}

	try {
		queueUrl = _internal_urls_per_host.at(host);
	}
	catch (Exception& e) {
		cerr << e.name() << " | " << e.displayText() << " | " << e.message() << endl;
	}
	
	queueUrl.push(url);
	_internal_urls_per_host.insert_or_assign(host,queueUrl);
	mlock.unlock();	// unlock before notificiation to minimize mutex contention
	cond_multi_.notify_one();  // notify one waiting thread
}

vector<string> Frontier::GetQueuesKeys()
{
	vector<string> dnsNames;
	vector<string>::iterator vit;

	vit = dnsNames.begin();
	for (map<string, queue<Url>>::const_iterator iter = _internal_urls_per_host.begin(); iter != _internal_urls_per_host.end(); iter++)
	{
		string key  = iter->first;
		dnsNames.insert(vit,key);
	}
	return dnsNames;
}

queue<Url> Frontier::GetUrlQueue(string ip_host_key)
{
	unique_lock<mutex> mlock(mutex_multi_); // mutex scope lock
	while (_internal_urls_per_host.empty()) // check condition to be safe against spurious wakes
	{
		cond_multi_.wait(mlock); // release lock and go join the waiting thread queue
	}
	queue<Url> queueByHost = _internal_urls_per_host.at(ip_host_key);
	_internal_urls_per_host.erase(ip_host_key);
	return queueByHost;
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
	if (_it == _internal_downloaded_urls.end()) 
	{   // Only add URL to frontier repo if it hasn't been crawled yet
		unique_lock<mutex> mlock(mutex_);
		_internal_fifo_struct.push(s);
		mlock.unlock();	// unlock before notificiation to minimize mutex contention
		cond_.notify_one();  // notify one waiting thread
	}
}


void Frontier::ArchiveUrl(size_t url_hash)
{
	_internal_downloaded_urls.push_back(url_hash);
}

Url Frontier::GetUrl()
{
	Url url("");

	unique_lock<mutex> mlock(mutex_); // mutex scope lock
	while (_internal_fifo_struct.empty()) // check condition to be safe against spurious wakes
	{
		cond_.wait(mlock); // release lock and go join the waiting thread queue
	}

	if (!_internal_fifo_struct.empty()) {
		url = _internal_fifo_struct.front();
		_internal_fifo_struct.pop();
	}
	return url;
}


bool Frontier::IsEmpty()
{
	return _internal_fifo_struct.empty();
}
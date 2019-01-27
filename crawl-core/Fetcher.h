#ifndef __FETCHER_H
#define __FETCHER_H

#include <thread>
#include <sstream>
#include <iostream>
#include <string>

#include "Frontier.h"
#include "Resolver.h"

#ifdef _WIN32
#include <io.h>

#else
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#endif

#define HTTP_DEFAULT_PORT 8080 


#include "Poco/URIStreamOpener.h"
#include "Poco/StreamCopier.h"
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include "Poco/Net/HTTPStreamFactory.h"
#include "Poco/Net/FTPStreamFactory.h"
#include "Poco/Net/HTTPClientSession.h"
#include <memory>

using Poco::URIStreamOpener;
using Poco::StreamCopier;
using Poco::Path;
using Poco::URI;
using Poco::Exception;
using Poco::Net::HTTPStreamFactory;
using Poco::Net::FTPStreamFactory;

class Fetcher
{
public:
	Fetcher(std::vector<std::string> seeds, int nseeds);
	~Fetcher();

	Frontier FrontierURLs;
	Resolver DNSResolver;

	void Run();
	void DownloadURL(std::string,Url);

private:
	Utils Misc;

	//bool doRequest(Poco::Net::HTTPClientSession& session, Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
};


#endif
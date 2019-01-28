#include "Fetcher.h"

using namespace std;

Fetcher::Fetcher(vector<string> seeds, int nseed)
{
	FrontierURLs.Fill(seeds, nseed);
	FrontierURLs.AssignUrl(&DNSResolver);
}

Frontier *frontier;
Fetcher *executer;
Resolver *resolver;


Fetcher::~Fetcher()
{
}

//
//bool Fetcher::doRequest(Poco::Net::HTTPClientSession& session, Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response)
//{
//	session.sendRequest(request);
//	std::istream& rs = session.receiveResponse(response);
//	std::cout << response.getStatus() << " " << response.getReason() << std::endl;
//	if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED)
//	{
//		StreamCopier::copyStream(rs, std::cout);
//		return true;
//	}
//	else
//	{
//		Poco::NullOutputStream null;
//		StreamCopier::copyStream(rs, null);
//		return false;
//	}
//}


void Fetcher::DownloadURL(string host_ip, Url url)
{
	cout << "Downloading " << url.Value <<  " on thread " << this_thread::get_id()  <<  endl;
	HTTPStreamFactory::registerFactory();
	FTPStreamFactory::registerFactory();

	try
	{
		URI uri(url.Value);
		unique_ptr<istream> pStr(URIStreamOpener::defaultOpener().open(uri));
		StreamCopier::copyStream(*pStr.get(), cout);
	}
	catch (Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
		return;
	}

	//URI uri(url.Value);
	//string path(uri.getPathAndQuery());
	////string username = "", password = "";
	////Poco::Net::HTTPCredentials::extractCredentials(uri, username, password);
	////Poco::Net::HTTPCredentials credentials(username, password);
	//HTTPClientSession session(uri.getHost(), uri.getPort());
	//HTTPRequest request(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
	//HTTPResponse response;
	//try {
	//	if (!doRequest(session, request, response))
	//	{
	//		//credentials.authenticate(request, response);
	//		if (!doRequest(session, request, response))
	//		{
	//			std::cerr << "Invalid username or password" << std::endl;
	//			return;
	//		}
	//	}
	//}
	//catch (Exception& exc)
	//{
	//	std::cerr << exc.displayText() << std::endl;
	//	return;
	//}
}

void CrawlBatch(string host)
{
	queue<Url> urls = frontier->GetUrlQueue(host);
	string urlValue;
	size_t urlId;
	while (!urls.empty()) {
		try {
			Url url = urls.front();
			urls.pop();
			urlValue = url.Value;
			urlId = url.UniqueId;
			executer->DownloadURL(host, url);							/// Use resolved IP address to download HTML pages
			frontier->ArchiveUrl(url.UniqueId);			/// Add downloaded URL to list of already seen URLs (UST/DUE) in the frontier repo
			/// Extract links/URLs from within HTML pages
			/// Validate URLs, assign a weight to each URL object, discard unrelevant URLs
			/// Push extracted and validated URLs to Frontier
		}
		catch (Exception& e) 
		{
			cerr << "Error while trying to crawl " << urlId << ":" << urlValue << endl;
			cerr << e.displayText() << endl;
			cerr << e.message() << endl;
		}
	}
}


void readFrontier()
{
	do {
		frontier->AssignUrl(resolver);
	} while (!frontier->IsEmpty());
}

void crawlQueues() 
{
	vector<string> hosts = frontier->GetQueuesKeys();
	for_each(hosts.begin(), hosts.end(), CrawlBatch); // TBD: turn this into a parallel foreach
}

void Fetcher::Run()
{
	std::vector<std::thread> threadList;
	///thread threadList[2];

	executer = this;
	resolver = &DNSResolver;
	frontier = &FrontierURLs;

	//// TASK #1 - Keep extracting URLs and assigning them to queues per host (DNS)
	threadList.push_back(thread(readFrontier));

	//// TASK #2 -  KEEP creating threads for each queue per host	
	threadList.push_back(thread(crawlQueues));

	/// Wait for main thread to finish
	///main_thread.join();
	for_each(threadList.begin(), threadList.end(), mem_fn(&thread::join));
	
}
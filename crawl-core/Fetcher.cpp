#include "Fetcher.h"


using namespace std;



Fetcher::Fetcher(vector<string> seeds, int nseed)
{
	FrontierURLs.Fill(seeds, nseed);
}


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

void crawl_batch_fn(Fetcher *executer)
{
	Url url = executer->FrontierURLs.GetUrl();					/// Get URL from Frontier repository
	string host_ip = executer->DNSResolver.Resolve(url);		/// Resolve DNS via DNS servers
	executer->DownloadURL(host_ip, url);							/// Use resolved IP address to download HTML pages
	executer->FrontierURLs.ArchiveUrl(url.UniqueId);			/// Add downloaded URL to list of already seen URLs (UST/DUE) in the frontier repo
	/// Extract links/URLs from within HTML pages
	/// Validate URLs, assign a weight to each URL object, discard unrelevant URLs
	/// Push extracted and validated URLs to Frontier
}

void Fetcher::Run()
{
	std::vector<std::thread> threadList;

	do {
		///threadList.push_back(thread((f, this)));
		threadList.push_back(std::thread(crawl_batch_fn, this));
	} while (!FrontierURLs.IsEmpty());
	/// Wait for main thread to finish
	///main_thread.join();
	std::for_each(threadList.begin(), threadList.end(), std::mem_fn(&std::thread::join));
	
}
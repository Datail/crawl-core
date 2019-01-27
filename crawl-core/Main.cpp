#include "Main.h"
#include "Fetcher.h"

int main() 
{

	std::vector<std::string> urls;
	
	urls.push_back("http://oxxogas.com/dondehaygasolina/");
	urls.push_back("http://tarjetapetro-7.com.mx/Petro7.FuelAvailability/");
	//urls.push_back("http://www.google.com/");
	//urls.push_back("http://github.com/pocoproject/poco/blob/develop/Net/samples/download/src/download.cpp");

	Fetcher fetcher(urls, 2); /// Pass some seed URLs
	fetcher.Run();
	return 0;
}


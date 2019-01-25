#include "Main.h"
#include "Fetcher.h"

int main() 
{

	vector<string> urls;
	
	urls.push_back("http://oxxogas.com/dondehaygasolina/");
	urls.push_back("https://tarjetapetro-7.com.mx/Petro7.FuelAvailability/");

	Fetcher fetcher(urls, 2); /// Pass some seed URLs
	fetcher.Run();
	return 0;
}


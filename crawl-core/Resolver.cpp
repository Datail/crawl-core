#include "Resolver.h"

using namespace std;

Resolver::Resolver()
{
}


Resolver::~Resolver()
{
}



string Resolver::Resolve(Url url)
{
	misc.net_init();

	char ipstr[INET6_ADDRSTRLEN];
	struct addrinfo hints, *results, *item;

	memset(&hints, 0, sizeof hints);
	
	hints.ai_family = AF_UNSPEC;  /* AF_INET6 to force version */
	hints.ai_socktype = SOCK_STREAM;
	
	vector<string> parts = misc.Split(url.Value, '/');
	const char *hostname = const_cast<char*>(parts.at(2).c_str());

	int status = 0;
	if ((status = getaddrinfo(hostname, NULL, &hints, &results)) != 0)
	{
		cerr << "Error while trying to resolve hostname: " << hostname << ": " << gai_strerror(status) << endl;
		return "";
	}
	string ipver;

	for (item = results; item != NULL; item = item->ai_next)
	{
		void* addr;

		/* get pointer to the address itself */
		/* different fields in IPv4 and IPv6 */
		if (item->ai_family == AF_INET)  /* address is IPv4 */
		{
			struct sockaddr_in* ipv4 = (struct sockaddr_in*)item->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		}
		else  /* address is IPv6 */
		{
			struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)item->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}

		/* convert IP to a string and print it */
		inet_ntop(item->ai_family, addr, ipstr, sizeof ipstr);
	}

	misc.net_deinit();
	freeaddrinfo(results);

	cout << "Hostname: " << hostname << " ( " << ipver << " ): " << ipstr << endl;
	return ipstr;
}
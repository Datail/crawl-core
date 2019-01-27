#include "Utils.h"

using namespace std;

Utils::Utils()
{
}


Utils::~Utils()
{
}



char Utils::net_init(void)
{
#ifdef _WIN32
	return (WSAStartup(MAKEWORD(2, 2), &g_wsa_data) == NO_ERROR);
#else
	return 1;
#endif;
}

void Utils::net_deinit(void)
{
#ifdef _WIN32
	WSACleanup();
#endif
}



vector<string> Utils::Split(string src, char token)
{
	vector<string> strings;
	istringstream f(src);
	string s;

	while (getline(f, s, token)) {
		strings.push_back(s);
	}
	return strings;
}
#include "Url.h"

using namespace std;

Url::Url(string sz_value)
{
	UniqueId = hash<string>{}(sz_value);
	Value = sz_value;
	AlreadyDownloaded = false;
}


Url::~Url()
{
}

#pragma once
#define CURL_STATICLIB
#include "curl.h"
#include <iostream>


using namespace std;

static size_t write_data(void* ptr, size_t size, size_t mem, void* param)
{
	string& text = *static_cast<string*>(param);
	size_t tsize = size * mem;
	text.append(static_cast<char*>(ptr), tsize);
	return tsize;
}

int main()
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
	string data;
	CURL* curl = curl_easy_init();
	int ret = 1;
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "https://www.youtube.com/");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		CURLcode res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		ret = 0;
	}
	curl_global_cleanup();
	return ret;

}


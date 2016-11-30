#include "Update.h"

static size_t write_data(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

Update::~Update() {}

Update::Update(){}

bool Update::checkVersion() {
	CURL *curl = curl_easy_init();
	CURLcode res;
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "http://fisab.ru/tanks/version");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &version);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	if (res == CURLE_OK && strcmp(version.c_str(), curVersion.c_str()) != 0) {
		std::cout << "Avaible new version: " + Update::version << std::endl;
		return true;
	}
	else {
		std::cout << "You use newest version! " + Update::version + "  c:" << std::endl;
	}
	return false;
}

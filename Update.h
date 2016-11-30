#ifndef UPDATE_H
#define UPDATE_H

#pragma comment(lib,"libcurld.lib")

#include <curl/curl.h>
#include <stdio.h>
#include <iostream>
#include <string>

class Update
{
public:
	Update();
	~Update();

	std::string version;
	std::string curVersion = "0.01a";

	bool checkVersion();
};

#endif

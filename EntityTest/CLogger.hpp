#pragma once

#include <string>
#include <iostream>

#include <windows.h>

class CLogger final
{
public:
	static void Log(const std::string &message)
	{
		//std::cout << message << std::endl;
		OutputDebugStringA( ( message + '\n' ).c_str());
	};
};


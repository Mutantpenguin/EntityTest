#pragma once

#include <string>
#include <iostream>

#ifdef WIN32
	#include <windows.h>
#endif

class CLogger final
{
public:
	static void Log( const std::string &message )
	{
		#ifdef WIN32
			OutputDebugStringA( ( message + '\n' ).c_str() );
		#else
			std::cout << message << std::endl;
		#endif
	};
};


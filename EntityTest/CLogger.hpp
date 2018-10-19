#pragma once

#include <string>
#include <iostream>

#ifdef WIN32
	#include <windows.h>
#endif

#define OUTPUT_DEBUG

class CLogger final
{
public:
	static void Info( const std::string &message )
	{
		Log( message );
	};

	static void Debug( const std::string &message )
	{
#ifdef OUTPUT_DEBUG
		Log( message );
#endif
	};

private:
	static void Log( const std::string &message )
	{
#ifdef WIN32
		OutputDebugStringA( ( message + '\n' ).c_str() );
#else
		std::cout << message << std::endl;
#endif
	};
};


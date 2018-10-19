#include "CLogger.hpp"

#include <iostream>

#ifdef WIN32
	#include <windows.h>
#endif

//#define OUTPUT_DEBUG

void CLogger::Info( const std::string &message )
{
	Log( message );
};

void CLogger::Debug( const std::string &message )
{
#ifdef OUTPUT_DEBUG
	Log( message );
#endif
};

void CLogger::Log( const std::string &message )
{
#ifdef WIN32
	OutputDebugStringA( ( message + '\n' ).c_str() );
#else
	std::cout << message << std::endl;
#endif
};

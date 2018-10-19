#pragma once

#include <string>

class CLogger final
{
public:
	static void Info( const std::string &message );

	static void Debug( const std::string &message );

private:
	static void Log( const std::string &message );
};


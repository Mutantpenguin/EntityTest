#pragma once

#include <cstdint>
#include <string>

class CDummyComponent final
{
public:
	CDummyComponent();
	~CDummyComponent();

	std::uint16_t someInteger;

	std::string someString;
};


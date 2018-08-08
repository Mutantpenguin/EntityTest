#pragma once

class CBaseSystem
{
public:
	CBaseSystem()
	{}

	virtual ~CBaseSystem()
	{}

	virtual void Process() = 0;

	bool Paused = false;
};


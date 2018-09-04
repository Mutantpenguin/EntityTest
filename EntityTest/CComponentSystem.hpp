#pragma once

class CComponentSystem
{
public:
	CComponentSystem()
	{}

	virtual ~CComponentSystem()
	{}

	virtual void Process() = 0;

	bool Paused = false;
};


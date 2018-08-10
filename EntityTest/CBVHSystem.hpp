#pragma once

#include "CBaseSystem.hpp"

#include "MyECS.hpp"

#include "COcTree.hpp"

class CBVHSystem : public CBaseSystem
{
public:
	CBVHSystem( MyECS &ecs, const CBoundingBox &region ) :
		m_ecs { ecs },
		m_octree( region )
	{}

	~CBVHSystem()
	{};

	virtual void Process();

private:
	MyECS &m_ecs;

	// TODO separate OCTrees for static and dynamic objects
	COcTree m_octree;
};


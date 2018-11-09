#pragma once

#include "CComponentSystem.hpp"

template< typename T_ecs >
class CMovementSystem final : public CComponentSystem< T_ecs >
{
public:
	CMovementSystem( T_ecs &ecs ) :
		CComponentSystem { ecs }
	{}

	~CMovementSystem()
	{};

	virtual void Process() override
	{
		MTR_BEGIN( "CMovementSystem", "CMovementSystem::Process" );

		CLogger::Debug( "\tprocessing: CMovementSystem" );

		m_ecs.ForEach<CMovementComponent>( [ this ] ( const auto &entity, auto movementComponent )
		{
			auto spatialComponent = m_ecs.GetComponent<CTransformComponent>( entity );
			if( spatialComponent )
			{
				spatialComponent->Position += movementComponent->Direction;
			}

			auto physicsComponent = m_ecs.GetComponent<CPhysicsComponent>( entity );
		} );

		MTR_END( "CMovementSystem", "CMovementSystem::Process" );
	}
};


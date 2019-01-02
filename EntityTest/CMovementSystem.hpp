#pragma once

#include "ecs/ComponentSystemBase.hpp"

template< typename T_ecs >
class CMovementSystem final : public ecs::ComponentSystemBase< T_ecs >
{
public:
	CMovementSystem( T_ecs &ecs ) :
		ComponentSystemBase { ecs }
	{}

	virtual ~CMovementSystem()
	{};

	virtual void Process() override
	{
		MTR_BEGIN( "CMovementSystem", "CMovementSystem::Process" );

		CLogger::Debug( "\tprocessing: CMovementSystem" );

		m_ecs.ForEachComponent<Movement>( [ this ] ( const auto &entity, auto movementComponent )
		{
			auto transformComponent = m_ecs.GetComponent<Transform>( entity );
			if( transformComponent )
			{
				transformComponent->Position += movementComponent->Direction;
			}
		} );

		MTR_END( "CMovementSystem", "CMovementSystem::Process" );
	}
};


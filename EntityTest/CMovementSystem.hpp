#pragma once

#include "ecs/CComponentSystem.hpp"

template< typename T_ecs >
class CMovementSystem final : public ecs::CComponentSystem< T_ecs >
{
public:
	CMovementSystem( T_ecs &ecs ) :
		CComponentSystem { ecs }
	{}

	virtual ~CMovementSystem()
	{};

	virtual void Process() override
	{
		MTR_BEGIN( "CMovementSystem", "CMovementSystem::Process" );

		CLogger::Debug( "\tprocessing: CMovementSystem" );

		m_ecs.ForEach<cmpt::Movement>( [ this ] ( const auto &entity, auto movementComponent )
		{
			auto transformComponent = m_ecs.GetComponent<cmpt::Transform>( entity );
			if( transformComponent )
			{
				transformComponent->Position += movementComponent->Direction;
			}
		} );

		MTR_END( "CMovementSystem", "CMovementSystem::Process" );
	}
};


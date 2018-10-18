#include "CMovementSystem.hpp"

#include "minitrace.h"

void CMovementSystem::Process()
{
	MTR_SCOPE( "CMovementSystem", "CMovementSystem::Process" );

	CLogger::Log( "\tprocessing: CMovementSystem" );
	
	m_ecs.ForEach<CMovementComponent>( [ this ] ( const auto &entity, auto movementComponent )
	{
		auto spatialComponent = m_ecs.GetComponent<CTransformComponent>( entity );
		if( spatialComponent )
		{
			spatialComponent->Position += movementComponent->Direction;
		}
	} );
}
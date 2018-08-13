#include "CMovementSystem.hpp"

void CMovementSystem::Process()
{
	m_ecs.ForEach<CMovementComponent>( [ this ] ( const auto &entity, auto movementComponent )
	{
		auto transformComponent = m_ecs.GetComponent<CTransform>( entity );
		if( transformComponent )
		{
			transformComponent->Position += movementComponent->Direction;
		}
	} );
}
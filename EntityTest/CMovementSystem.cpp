#include "CMovementSystem.hpp"

void CMovementSystem::Run()
{
	m_ecs.ForEach<CMovementComponent>( [ this ] ( const auto &entity, auto movementComponent )
	{
		auto transformComponent = m_ecs.GetComponent<CTransformComponent>( entity );
		if( transformComponent )
		{
			transformComponent->Position += movementComponent->Direction;
		}
	} );
}
#pragma once

#include "ecs/CComponentSystem.hpp"

template< typename T_ecs >
class CHealthSystem final : public ecs::CComponentSystem< T_ecs >
{
public:
	CHealthSystem( T_ecs &ecs ) :
		CComponentSystem( ecs )
	{}

	~CHealthSystem()
	{};

	virtual void Process() override
	{
		MTR_BEGIN( "CHealthSystem", "CHealthSystem::Process" );

		CLogger::Debug( "\tprocessing: CHealthSystem" );

		std::vector< ecs::CEntity > entitiesForDeletion;

		m_ecs.ForEach< cmpt::Health >( [ &entitiesForDeletion ] ( const auto &healthEntity, auto healthComponent )
		{
			if( healthComponent->health <= 0.0f )
			{
				entitiesForDeletion.push_back( healthEntity );
			}
		} );

		for( const auto &entity : entitiesForDeletion )
		{
			m_ecs.Destroy( entity );
		}

		if( entitiesForDeletion.size() > 0 )
		{
			CLogger::Debug( "\t\tdestroyed " + std::to_string( entitiesForDeletion.size() ) + " entities" );
		}

		MTR_END( "CHealthSystem", "CHealthSystem::Process" );
	}
};

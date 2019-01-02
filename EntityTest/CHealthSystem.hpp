#pragma once

#include "ecs/ComponentSystemBase.hpp"

template< typename T_ecs >
class CHealthSystem final : public ecs::ComponentSystemBase< T_ecs >
{
public:
	CHealthSystem( T_ecs &ecs ) :
		ComponentSystemBase( ecs )
	{}

	virtual ~CHealthSystem()
	{};

	virtual void Process() override
	{
		MTR_BEGIN( "CHealthSystem", "CHealthSystem::Process" );

		CLogger::Debug( "\tprocessing: CHealthSystem" );

		std::vector< ecs::Entity > entitiesForDeletion;

		m_ecs.ForEachComponent< Health >( [ &entitiesForDeletion ] ( const auto &healthEntity, auto healthComponent )
		{
			if( healthComponent->health <= 0.0f )
			{
				entitiesForDeletion.push_back( healthEntity );
			}
		} );

		for( auto &entity : entitiesForDeletion )
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

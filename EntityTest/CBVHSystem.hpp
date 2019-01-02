#pragma once

#include <memory>

#include "ecs/ComponentSystemBase.hpp"

#include "CBVHBase.hpp"

template< typename T_ecs >
class CBVHSystem final : public ecs::ComponentSystemBase< T_ecs >
{
public:
	CBVHSystem( T_ecs &ecs, const std::shared_ptr< CBVHBase > &bvh ) :
		ComponentSystemBase( ecs ),
		m_bvh { bvh }
	{
		Process();
	}

	virtual ~CBVHSystem()
	{};

	virtual void Process() override
	{
		MTR_BEGIN( "CBVHSystem", "CBVHSystem::Process" );

		CLogger::Debug( "\tprocessing: CBVHSystem" );

		const auto start = std::chrono::high_resolution_clock::now();

		m_bvh->Clear();

		std::vector< ecs::Entity > entitiesForDeletion;

		m_ecs.ForEachComponent<Transform>( [ this, &entitiesForDeletion ] ( const auto &transformEntity, const auto transformComponent )
		{
			auto const boundingBox = m_ecs.GetComponent<BoundingBox>( transformEntity );

			if( !m_bvh->Add( transformEntity, transformComponent->Position, boundingBox ) )
			{
				entitiesForDeletion.push_back( transformEntity );
			}
		} );

		for( auto &entity : entitiesForDeletion )
		{
			m_ecs.Destroy( entity );
		}

		if( entitiesForDeletion.size() > 0 )
		{
			CLogger::Debug( "\t\tdestroyed " + std::to_string( entitiesForDeletion.size() ) + " entities which dropped out of the world" );
		}

		const auto end = std::chrono::high_resolution_clock::now();
		const std::chrono::duration<f32> diff = end - start;
		CLogger::Debug( "\t\trebuilding bvh system: " + std::to_string( diff.count() * 1000.0f ) + " ms" );

		MTR_END( "CBVHSystem", "CBVHSystem::Process" );
	}

private:
	// TODO separate spatial for static and dynamic objects
	const std::shared_ptr< CBVHBase > m_bvh;
};

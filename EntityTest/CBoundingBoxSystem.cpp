#include "CBoundingBoxSystem.hpp"

#include "minitrace.h"

void CBoundingBoxSystem::Process()
{
	MTR_SCOPE( "CBoundingBoxSystem", "CBoundingBoxSystem::Process" );

	CLogger::Log( "\tprocessing: CBoundingBoxSystem" );
	
	m_ecs.ForEach<CBoundingBox>( [ this ] ( const auto &entity, auto boundingBox )
	{
		auto transformComponent = m_ecs.GetComponent<CTransform>( entity );
		if( transformComponent )
		{
			boundingBox->MoveTo( transformComponent->Position );
		}
	} );
}
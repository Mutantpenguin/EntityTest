#pragma once

namespace ecs
{
	template< typename T_ecs >
	class ComponentSystemBase
	{
	public:
		ComponentSystemBase( T_ecs &ecs ) :
			m_ecs { ecs }
		{}

		virtual ~ComponentSystemBase()
		{}

		virtual void Process() = 0;

		bool Paused = false;

	protected:
		T_ecs &m_ecs;
	};
}
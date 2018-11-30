#pragma once

namespace ecs
{
	template< typename T_ecs >
	class CComponentSystem
	{
	public:
		CComponentSystem( T_ecs &ecs ) :
			m_ecs { ecs }
		{}

		virtual ~CComponentSystem()
		{}

		virtual void Process() = 0;

		bool Paused = false;

	protected:
		T_ecs &m_ecs;
	};
}
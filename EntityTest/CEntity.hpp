#ifndef CENTITY_HPP
#define CENTITY_HPP

#include <string>
#include <memory>
#include <array>
#include <typeindex>

#include "CLogger.hpp"

#include "EComponentIndex.hpp"

#include "CTransform.hpp"
#include "CBoundingBox.hpp"

class CBaseComponent;

class CEntity final : public std::enable_shared_from_this<CEntity>
{
	friend class CScene;

public:
	explicit CEntity( const std::string &name, const std::uint16_t sceneId );
	~CEntity();

	const std::string &Name( void ) const;

	template< typename T, typename... Args >
	std::shared_ptr<T> Add( Args... args )
	{
		if( m_components[ T::Index ] != nullptr )
		{
			CLogger::Log( "entity '" + m_name + "' with id '" + std::to_string( Id ) + "' already has a component of type '" + typeid( T ).name() + "'" );

			return( nullptr );
		}
		else
		{
			auto component = std::make_shared< T >( shared_from_this(), args... );
			m_components[ T::Index ] = component;

			return( component );
		}
	};

	template< typename T >
	void Remove()
	{
		if( !HasComponents<T>() )
		{
			CLogger::Log( "entity '" + m_name + "' with id '" + std::to_string( Id ) + "' does not have a component of type '" + typeid( T ).name() + "'" );
		}
		else
		{
			m_components[ T::Index ] = nullptr;
		}
	};

	template< typename T >
	std::shared_ptr< T > Get() const
	{
		const auto component = m_components[ T::Index ];

		if( nullptr == component )
		{
			CLogger::Log( "entity '" + m_name + "' with id '" + std::to_string( Id ) + "' does not have a component of type '" + typeid( T ).name() + "'" );

			return( nullptr );
		}
		else
		{
			return( std::static_pointer_cast<T>( component ) );
		}
	};

	template < typename T >
	bool HasComponents() const
	{
		if( m_components[ T::Index ] == nullptr )
		{
			return( false );
		}
		else
		{
			return( true );
		}
	};

	template < typename First, typename Second, typename ... Rest >
	bool HasComponents() const
	{
		return( HasComponents<First>() && HasComponents<Second, Rest...>() );
	};

	const std::uint32_t Id = ++s_lastId;

	CTransform Transform;
	CBoundingBox BoundingBox;

private:
	std::array< std::shared_ptr< CBaseComponent >, static_cast<std::uint16_t>( EComponentIndex::MAX ) > m_components;

	const std::string m_name;

	const std::uint16_t m_sceneId;

	static std::uint32_t s_lastId;
};

#endif // COBJECT_HPP
#ifndef CENTITY_HPP
#define CENTITY_HPP

#include <string>
#include <memory>
#include <unordered_map>
#include <typeindex>

#include "CLogger.hpp"

#include "CTransform.hpp"

class CBaseComponent;

class CEntity final : public std::enable_shared_from_this<CEntity>
{
	friend class CScene;

public:
	explicit CEntity(const std::string &name, const std::uint16_t sceneId);
	~CEntity();

	const std::string &Name(void) const;

	template< typename T, typename... Args >
	std::shared_ptr<T> Add( Args... args )
	{
		auto type_index = std::type_index(typeid(T));

		const auto it = m_components.find(type_index);

		if (it != std::cend(m_components))
		{
			CLogger::Log("entity '" + m_name + "' with id '" + std::to_string(Id) + "' already has a component of type '" + typeid(T).name() + "'" );

			return(nullptr);
		}
		else
		{
			auto component = std::make_shared< T >(shared_from_this(), args...);
			m_components.insert( std::make_pair(type_index, component ) );

			return(component);
		}
	};

	template< typename T, typename... Args >
	void Remove()
	{
		auto type_index = std::type_index(typeid(T));

		const auto it = m_components.find(type_index);

		if (it == std::cend(m_components))
		{
			CLogger::Log("entity '" + m_name + "' with id '" + std::to_string(Id) + "' does not have a component of type '" + typeid(T).name() + "'");
		}
		else
		{
			m_components.erase(it);
		}
	};

	template< typename T, typename... Args >
	std::shared_ptr< T > Get()
	{
		auto type_index = std::type_index(typeid(T));

		const auto it = m_components.find(type_index);

		if (it == std::cend(m_components))
		{
			CLogger::Log("entity '" + m_name + "' with id '" + std::to_string(Id) + "' does not have a component of type '" + typeid(T).name() + "'");

			return(nullptr);
		}
		else
		{
			return(std::static_cast<T>(*it));
		}
	};

	template < typename Last >
	bool HasComponents() const
	{
		const auto it = m_components.find(std::type_index(typeid(Last)));

		if (it == std::cend(m_components))
		{
			return(false);
		}
		else
		{
			return(true);
		}
	};

	template < typename First, typename Second, typename ... Rest >
	bool HasComponents() const
	{
		return(HasComponents<First>() && HasComponents<Second, Rest...>());
	};

	const std::uint32_t Id = ++s_lastId;

	CTransform Transform;

private:
	std::unordered_map< std::type_index, const std::shared_ptr< CBaseComponent > > m_components;

	const std::string m_name;

	const std::uint16_t m_sceneId;

	static std::uint32_t s_lastId;
};

#endif // COBJECT_HPP
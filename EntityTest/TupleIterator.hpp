#pragma once

class TupleIterator
{
public:
	template< std::size_t I = 0, typename FuncT, typename... Types >
	static inline typename std::enable_if<I == sizeof...( Types ), void>::type
		for_each( std::tuple< Types... > &, FuncT ) // Unused arguments are given no names.
	{}

	template<std::size_t I = 0, typename FuncT, typename... Types>
	static inline typename std::enable_if<I < sizeof...( Types ), void>::type
		for_each( std::tuple< Types... >& t, FuncT f )
	{
		f( std::get<I>( t ) );
		for_each<I + 1, FuncT, Types...>( t, f );
	}
};


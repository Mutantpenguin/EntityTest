#pragma once

class TupleIterator
{
public:
	template <typename Tuple, typename F>
	static void for_each( Tuple&& tuple, F&& f )
	{
		constexpr size_t N = std::tuple_size<std::remove_reference_t<Tuple>>::value;
		for_each_impl( std::forward<Tuple>( tuple ), std::forward<F>( f ),
					   std::make_index_sequence<N>{} );
	}

private:
	template <typename Tuple, typename F, size_t ...Indices>
	static void for_each_impl( Tuple&& tuple, F&& f, std::index_sequence<Indices...> )
	{
		using swallow = int[];
		(void)swallow
		{
			1,
				( f( std::get<Indices>( std::forward<Tuple>( tuple ) ) ), void(), int {} )...
		};
	}
};


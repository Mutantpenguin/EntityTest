#ifndef CSIZE_H
#define CSIZE_H

#include <utility>
#include <cstdint>

#include "Types.hpp"

struct CSize
{
public:
	CSize()
	{};

	CSize( const u32 p_width, const u32 p_height ) :
		width { p_width },
		height { p_height }
	{};

	CSize( const CSize &size ) :
		width { size.width },
		height { size.height }
	{};

	CSize& operator = ( CSize size )
	{
		std::swap( width, size.width );
		std::swap( height, size.height );

		return( *this );
	};

	inline bool operator == ( const CSize &size ) const
	{
		return( ( width == size.width ) && ( height == size.height ) );
	};

	inline bool operator != ( const CSize &size ) const
	{
		return( !( ( *this ) == size ) );
	};

	inline CSize& operator += ( const CSize &size )
	{
		width += size.width;
		height += size.height;

		return( *this );
	};

	inline CSize& operator -= ( const CSize &size )
	{
		width -= size.width;
		height -= size.height;

		return( *this );
	}

	u32 width { 0 };
	u32 height { 0 };
};

inline CSize operator + ( CSize lhs, const CSize &rhs )
{
	lhs += rhs;

	return( lhs );
}

inline CSize operator - ( CSize lhs, const CSize &rhs )
{
	lhs -= rhs;

	return( lhs );
}

#endif // CSIZE_H
#ifndef CSIZE_H
#define CSIZE_H

#include <utility>
#include <cstdint>

struct CSize
{
public:
	CSize() {};

	CSize(const std::uint32_t p_width, const std::uint32_t p_height) :
		width{ p_width },
		height{ p_height }
	{};

	CSize(const CSize &size) :
		width{ size.width },
		height{ size.height }
	{};

	CSize& operator = (CSize size)
	{
		std::swap(width, size.width);
		std::swap(height, size.height);

		return(*this);
	};

	inline bool operator == (const CSize &size) const
	{
		return((width == size.width) && (height == size.height));
	};

	inline bool operator != (const CSize &size) const
	{
		return(!((*this) == size));
	};

	inline CSize& operator += (const CSize &size)
	{
		width += size.width;
		height += size.height;

		return(*this);
	};

	inline CSize& operator -= (const CSize &size)
	{
		width -= size.width;
		height -= size.height;

		return(*this);
	}

	std::uint32_t width{ 0 };
	std::uint32_t height{ 0 };
};

inline CSize operator + (CSize lhs, const CSize &rhs)
{
	lhs += rhs;

	return(lhs);
}

inline CSize operator - (CSize lhs, const CSize &rhs)
{
	lhs -= rhs;

	return(lhs);
}

#endif // CSIZE_H
#include "CFrustum.hpp"

#include "Distance.hpp"

CFrustum::CFrustum( const glm::mat4 &viewProjectionMatrix ) :
	m_planes {	{
					// right
					{
						{
							viewProjectionMatrix[ 0 ][ 3 ] - viewProjectionMatrix[ 0 ][ 0 ],
							viewProjectionMatrix[ 1 ][ 3 ] - viewProjectionMatrix[ 1 ][ 0 ],
							viewProjectionMatrix[ 2 ][ 3 ] - viewProjectionMatrix[ 2 ][ 0 ]
						},
						viewProjectionMatrix[ 3 ][ 3 ] - viewProjectionMatrix[ 3 ][ 0 ]
					},

					// left
					{
						{
							viewProjectionMatrix[ 0 ][ 3 ] + viewProjectionMatrix[ 0 ][ 0 ],
							viewProjectionMatrix[ 1 ][ 3 ] + viewProjectionMatrix[ 1 ][ 0 ],
							viewProjectionMatrix[ 2 ][ 3 ] + viewProjectionMatrix[ 2 ][ 0 ]
						},
						viewProjectionMatrix[ 3 ][ 3 ] + viewProjectionMatrix[ 3 ][ 0 ]
					},

					// top
					{
						{
							viewProjectionMatrix[ 0 ][ 3 ] - viewProjectionMatrix[ 0 ][ 1 ],
							viewProjectionMatrix[ 1 ][ 3 ] - viewProjectionMatrix[ 1 ][ 1 ],
							viewProjectionMatrix[ 2 ][ 3 ] - viewProjectionMatrix[ 2 ][ 1 ]
						},
						viewProjectionMatrix[ 3 ][ 3 ] - viewProjectionMatrix[ 3 ][ 1 ]
					},

					// bottom
					{
						{
							viewProjectionMatrix[ 0 ][ 3 ] + viewProjectionMatrix[ 0 ][ 1 ],
							viewProjectionMatrix[ 1 ][ 3 ] + viewProjectionMatrix[ 1 ][ 1 ],
							viewProjectionMatrix[ 2 ][ 3 ] + viewProjectionMatrix[ 2 ][ 1 ]
						},
						viewProjectionMatrix[ 3 ][ 3 ] + viewProjectionMatrix[ 3 ][ 1 ]
					},

					// front
					{
						{
							viewProjectionMatrix[ 0 ][ 3 ] + viewProjectionMatrix[ 0 ][ 2 ],
							viewProjectionMatrix[ 1 ][ 3 ] + viewProjectionMatrix[ 1 ][ 2 ],
							viewProjectionMatrix[ 2 ][ 3 ] + viewProjectionMatrix[ 2 ][ 2 ]
						},
						viewProjectionMatrix[ 3 ][ 3 ] + viewProjectionMatrix[ 3 ][ 2 ]
					},

					// back
					{
						{
							viewProjectionMatrix[ 0 ][ 3 ] - viewProjectionMatrix[ 0 ][ 2 ],
							viewProjectionMatrix[ 1 ][ 3 ] - viewProjectionMatrix[ 1 ][ 2 ],
							viewProjectionMatrix[ 2 ][ 3 ] - viewProjectionMatrix[ 2 ][ 2 ]
						},
						viewProjectionMatrix[ 3 ][ 3 ] - viewProjectionMatrix[ 3 ][ 2 ]
					}
				}	}
{}

const std::array< CPlane, 6 > &CFrustum::Planes() const
{
	return( m_planes );
}
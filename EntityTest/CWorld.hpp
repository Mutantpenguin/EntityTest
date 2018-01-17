#ifndef CWORLD_HPP
#define CWORLD_HPP

#include <glm/glm.hpp>

class CWorld final
{
private:
	CWorld(const CWorld& rhs);
	CWorld& operator=(const CWorld& rhs);

public:
	CWorld();
	~CWorld();

	static const glm::vec3 Z;
	static const glm::vec3 Y;
	static const glm::vec3 X;
};

#endif // CWORLD_HPP
#include "CCallDodTest.hpp"

#include "CDodTest.hpp"

#include "CPhysicsComponent.hpp"
#include "CPlayerComponent.hpp"
#include "CDummyComponent.hpp"

CCallDodTest::CCallDodTest()
{}


CCallDodTest::~CCallDodTest()
{}

void CCallDodTest::test( const std::uint32_t numberOfEntities )
{
	CDodTest<CPlayerComponent, CPhysicsComponent> test;

	auto blah1 = test.GetComponentsArray<CPlayerComponent>();

	auto blah2 = test.GetComponentsArray<CPhysicsComponent>();
}
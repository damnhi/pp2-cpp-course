#include <iostream>
#include <type_traits>
#include <gtest/gtest.h>

#include "../shoot.h"


using namespace std;
using namespace ::testing;


struct ShootTester : public ::testing::Test
{
};

TEST_F(ShootTester, shootIsObject)
{
#ifdef UNIMPLEMENTED_shootIsObject
    ADD_FAILURE() << "Not implemented UNIMPLEMENTED_shootIsObject";
#else
    constexpr bool objectIsBaseForPlayer = std::is_base_of_v<Object, Shoot>;
    ASSERT_TRUE(objectIsBaseForPlayer);

    const Shoot shoot(Direction::RIGHT, Position{});

    ASSERT_EQ(ObjectType::OBJECT_SHOOT, shoot.type());
#endif
}

TEST_F(ShootTester, shootHasDirectionAndPosition)
{
#ifdef UNIMPLEMENTED_shootHasDirectionAndPosition
    ADD_FAILURE() << "Not implemented UNIMPLEMENTED_shootHasDirectionAndPosition";
#else
    const Position position(5, 6), positionToTheLeftAndDown(4, 5);
    const Direction direction = Direction::UP;

    Shoot shoot(direction, position);
    ASSERT_EQ(position.x(), shoot.position().x());
    ASSERT_EQ(position.y(), shoot.position().y());
    ASSERT_EQ(direction, shoot.direction());

    shoot.setPosition(positionToTheLeftAndDown);
    ASSERT_EQ(positionToTheLeftAndDown.x(), shoot.position().x());
    ASSERT_EQ(positionToTheLeftAndDown.y(), shoot.position().y());

    shoot.moveUp();
    shoot.moveRight();
    ASSERT_EQ(position.x(), shoot.position().x());
    ASSERT_EQ(position.y(), shoot.position().y());
#endif
}

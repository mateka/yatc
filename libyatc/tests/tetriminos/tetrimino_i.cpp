#define BOOST_TEST_MODULE tetrimino_i
#include <boost/test/unit_test.hpp>

#include <yatc/coordinate.h>
#include <yatc/tetriminos/tetrimino_i.h>
#include <yatc/tetriminos/tetrimino_base.h>
#include <yatc/rotation.h>
#include <yatc/shape.h>

using namespace yatc;

BOOST_AUTO_TEST_CASE(constructor)
{
	const tetrimino_base mold(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 0, 2 },
		shape::I
	);
	const tetrimino_i i;
	BOOST_TEST(i == mold);
}

BOOST_AUTO_TEST_CASE(rotate_i)
{
	tetrimino_i i1;
	tetrimino_i i2;
	i1.rotate(rotation::cw);
	i2.rotate(rotation::ccw);
	BOOST_TEST(i1 == i2);
}

BOOST_AUTO_TEST_CASE(rotate_cw_ccw)
{
	tetrimino_i i, other_i;
	i.rotate(rotation::cw);
	i.rotate(rotation::ccw);
	BOOST_TEST(i == other_i);
}

BOOST_AUTO_TEST_CASE(cw_2rotate)
{
	tetrimino_i i, other_i;
	i.rotate(rotation::cw);
	i.rotate(rotation::cw);
	BOOST_TEST(i == other_i);
}

BOOST_AUTO_TEST_CASE(ccw_2rotate)
{
	tetrimino_i i, other_i;
	i.rotate(rotation::ccw);
	i.rotate(rotation::ccw);
	BOOST_TEST(i == other_i);
}

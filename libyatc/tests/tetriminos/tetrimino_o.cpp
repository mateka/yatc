#define BOOST_TEST_MODULE tetrimino_o
#include <boost/test/unit_test.hpp>

#include <yatc/coordinate.h>
#include <yatc/tetriminos/tetrimino_o.h>
#include <yatc/tetriminos/tetrimino_base.h>
#include <yatc/rotation.h>
#include <yatc/shape.h>

using namespace yatc;

BOOST_AUTO_TEST_CASE(constructor)
{
	const tetrimino_base mold(
		coordinate{ 0, 0 }, coordinate{ 1, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 },
		shape::O
	);
	const tetrimino_o o;
	BOOST_TEST(o == mold);
}

BOOST_AUTO_TEST_CASE(cw_rotate)
{
	tetrimino_o o, other_o;
	o.rotate(rotation::cw);
	BOOST_TEST(o == other_o);
}

BOOST_AUTO_TEST_CASE(ccw_rotate)
{
	tetrimino_o o, other_o;
	o.rotate(rotation::ccw);
	BOOST_TEST(o == other_o);
}

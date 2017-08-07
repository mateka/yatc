#define BOOST_TEST_MODULE tetrimino_l
#include <boost/test/unit_test.hpp>

#include <yatc/coordinate.h>
#include <yatc/tetriminos/tetrimino_l.h>
#include <yatc/tetriminos/tetrimino_base.h>
#include <yatc/shape.h>

using namespace yatc;

BOOST_AUTO_TEST_CASE(constructor)
{
	const tetrimino_base mold(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 },
		shape::L
	);
	const tetrimino_l l;
	BOOST_TEST(l == mold);
}

#define BOOST_TEST_MODULE tetrimino_j
#include <boost/test/unit_test.hpp>

#include <yatc/coordinate.h>
#include <yatc/tetriminos/tetrimino_j.h>
#include <yatc/tetriminos/tetrimino_base.h>
#include <yatc/shape.h>

using namespace yatc;

BOOST_AUTO_TEST_CASE(constructor)
{
	const tetrimino_base mold(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ -1, 1 },
		shape::J
	);
	const tetrimino_j j;
	BOOST_TEST(j == mold);
}

#define BOOST_TEST_MODULE tetrimino_t
#include <boost/test/unit_test.hpp>

#include <yatc/coordinate.h>
#include <yatc/tetriminos/tetrimino_t.h>
#include <yatc/tetriminos/tetrimino_base.h>
#include <yatc/shape.h>

using namespace yatc;

BOOST_AUTO_TEST_CASE(constructor)
{
	const tetrimino_base mold(
		coordinate{ -1, 0 }, coordinate{ 0, 0 },
		coordinate{ 1, 0 }, coordinate{ 0, 1 },
		shape::T
	);
	const tetrimino_t t;
	BOOST_TEST(t == mold);
}

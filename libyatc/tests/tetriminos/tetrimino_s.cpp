#define BOOST_TEST_MODULE tetrimino_s
#include <boost/test/unit_test.hpp>

#include <yatc/coordinate.h>
#include <yatc/tetriminos/tetrimino_s.h>
#include <yatc/tetriminos/tetrimino_base.h>
#include <yatc/shape.h>

using namespace yatc;

BOOST_AUTO_TEST_CASE(constructor)
{
	const tetrimino_base mold(
		coordinate{ 0, 0 }, coordinate{ 1, 0 },
		coordinate{ -1, 1 }, coordinate{ 0, 1 },
		shape::S
	);
	const tetrimino_s s;
	BOOST_TEST(s == mold);
}

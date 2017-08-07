#define BOOST_TEST_MODULE tetrimino_base
#include <boost/test/unit_test.hpp>

#include <yatc/coordinate.h>
#include <yatc/tetriminos/tetrimino_base.h>
#include <yatc/rotation.h>
#include <yatc/shape.h>
#include <algorithm>

using namespace yatc;


BOOST_AUTO_TEST_CASE(constructor)
{
	const tetrimino_base t(
		coordinate{ -1, 0 }, coordinate{ 0, 0 },
		coordinate{ 1, 0 }, coordinate{ 0, 1 }
	);
	const std::array<coordinate, 4> pieces{
		coordinate{-1, 0}, coordinate{0, 0},
		coordinate{ 1, 0}, coordinate{ 0, 1 }
	};
	BOOST_TEST(std::equal(std::cbegin(t), std::cend(t), std::cbegin(pieces)));
}

BOOST_AUTO_TEST_CASE(constructor_with_tag)
{
	const tetrimino_base l(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }, shape::L
	);
	const std::array<coordinate, 4> pieces {
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }
	};
	BOOST_TEST(std::equal(std::cbegin(l), std::cend(l), std::cbegin(pieces)));
	BOOST_TEST(l.tag() == shape::L);
}

BOOST_AUTO_TEST_CASE(move_tetrimino_base)
{
	tetrimino_base l_before(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }
	);
	const coordinate v{ 5, 6 };
	const tetrimino_base l_after(
		coordinate{ 0, -1 } + v, coordinate{ 0, 0 } + v,
		coordinate{ 0, 1 } + v, coordinate{ 1, 1 } + v
	);
	l_before.move(v);
	BOOST_TEST(l_before == l_after);
}

BOOST_AUTO_TEST_CASE(rotate_tetrimino_base)
{
	tetrimino_base l_before(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }
	);
	const tetrimino_base l_after(
		coordinate{ -1, 0 }, coordinate{ 0, 0 },
		coordinate{ 1, 0 }, coordinate{ 1, -1 }
	);
	l_before.rotate(rotation::cw);
	BOOST_TEST(l_before == l_after);
}

BOOST_AUTO_TEST_CASE(rotate_tetrimino_base_cw_ccw)
{
	tetrimino_base l_before(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }
	);
	const tetrimino_base l_after(	// same as l_before
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }
	);
	l_before.rotate(rotation::cw);
	l_before.rotate(rotation::ccw);
	BOOST_TEST(l_before == l_after);
}

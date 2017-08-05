#define BOOST_TEST_MODULE coordinate
#include <boost/test/unit_test.hpp>

#include <yatc/coordinate.h>
#include <yatc/tetrimino.h>
#include <yatc/rotation.h>
#include <yatc/shape.h>
#include <algorithm>
using namespace yatc;

BOOST_AUTO_TEST_CASE(constructor)
{
	const tetrimino t(
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
	const tetrimino l(
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

BOOST_AUTO_TEST_CASE(equality)
{
	const tetrimino l(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }
	);
	const tetrimino other_l(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }
	);
	BOOST_TEST(l == other_l);
}

BOOST_AUTO_TEST_CASE(equality_with_tag)
{
	const tetrimino l(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }, shape::L
	);
	const tetrimino other_l(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }, shape::L
	);
	BOOST_TEST(l == other_l);
}

BOOST_AUTO_TEST_CASE(inequality)
{
	const tetrimino l(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }
	);
	const tetrimino t(
		coordinate{ -1, 0 }, coordinate{ 0, 0 },
		coordinate{ 1, 0 }, coordinate{ 0, 1 }
	);
	BOOST_TEST(l != t);
}

BOOST_AUTO_TEST_CASE(inequality_with_tag)
{
	const tetrimino l(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }, shape::L
	);
	const tetrimino other(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }, shape::T
	);
	BOOST_TEST(l != other);
}

BOOST_AUTO_TEST_CASE(move_tetrimino)
{
	tetrimino l_before(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }
	);
	const coordinate v{ 5, 6 };
	const tetrimino l_after(
		coordinate{ 0, -1 } + v, coordinate{ 0, 0 } + v,
		coordinate{ 0, 1 } + v, coordinate{ 1, 1 } + v
	);
	l_before.move(v);
	BOOST_TEST(l_before == l_after);
}

BOOST_AUTO_TEST_CASE(rotate_tetrimino)
{
	tetrimino l_before(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }
	);
	const tetrimino l_after(
		coordinate{ -1, 0 }, coordinate{ 0, 0 },
		coordinate{ 1, 0 }, coordinate{ 1, -1 }
	);
	l_before.rotate(rotation::cw);
	BOOST_TEST(l_before == l_after);
}

BOOST_AUTO_TEST_CASE(standalone_move_tetrimino)
{
	const tetrimino l_before(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }
	);
	const coordinate v{ 5, 6 };
	const tetrimino l_after(
		coordinate{ 0, -1 } +v, coordinate{ 0, 0 } +v,
		coordinate{ 0, 1 } +v, coordinate{ 1, 1 } +v
	);
	BOOST_TEST(move(l_before, v) == l_after);
}

BOOST_AUTO_TEST_CASE(standalone_rotate_tetrimino)
{
	const tetrimino l_before(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }
	);
	const tetrimino l_after(
		coordinate{ -1, 0 }, coordinate{ 0, 0 },
		coordinate{ 1, 0 }, coordinate{ 1, -1 }
	);
	BOOST_TEST(rotate(l_before, rotation::cw) == l_after);
}

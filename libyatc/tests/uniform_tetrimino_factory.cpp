#define BOOST_TEST_MODULE uniform_tetrimino_factory
#include <boost/test/unit_test.hpp>

#include <yatc/uniform_tetrimino_factory.h>
#include <yatc/tetriminos/tetriminos.h>

using namespace yatc;


BOOST_AUTO_TEST_CASE(next_tetrimino)
{
	uniform_tetrimino_factory factory(1);
	auto s = factory.next();
	const bool next_is_s = *s == tetrimino_s();
	BOOST_TEST(next_is_s);
}
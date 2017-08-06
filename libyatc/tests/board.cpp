#define BOOST_TEST_MODULE board
#include <boost/test/unit_test.hpp>

#include <yatc/board.h>
#include <yatc/shape.h>
#include <yatc/tetrimino.h>
using namespace yatc;


BOOST_AUTO_TEST_CASE(constructor)
{
	const board b;
	BOOST_TEST(b.rows_count() == 20);
	BOOST_TEST(b.columns_count() == 10);
}

BOOST_AUTO_TEST_CASE(const_indexer)
{
	const board b;
	BOOST_TEST(b(1, 9) == shape::unknown);
}

BOOST_AUTO_TEST_CASE(indexer)
{
	board b;
	BOOST_TEST(b(2, 0) == shape::unknown);
	b(8, 11) = shape::J;
	BOOST_TEST(b(8, 11) == shape::J);
}

BOOST_AUTO_TEST_CASE(free_cell)
{
	board b;
	BOOST_TEST(b.free(8, 11));
	b(8, 11) = shape::J;
	BOOST_TEST(b.free(0, 0));
	BOOST_TEST(!b.free(8, 11));
	BOOST_TEST(b.free(8, 12));
	BOOST_TEST(b.free(7, 11));
}

BOOST_AUTO_TEST_CASE(full_row)
{
	board b;
	const std::size_t row = 10;
	for (std::size_t i = 0; i < b.columns_count(); ++i)
		b(i, row) = shape::O;
	b(8, 11) = shape::J;
	BOOST_TEST(!b.full(11));
	BOOST_TEST(b.full(row));
	BOOST_TEST(!b.full(row - 1));
}

BOOST_AUTO_TEST_CASE(can_be_placed_outside_board)
{
	board b;
	b(8, 11) = shape::J;

	auto t = tetrimino::from(shape::I);
	BOOST_TEST(!b.can_be_placed(t));
}

BOOST_AUTO_TEST_CASE(can_be_placed_on_free_space)
{
	board b;
	b(8, 11) = shape::J;

	auto t = tetrimino::from(shape::O);
	t.move({1, 1});
	BOOST_TEST(b.can_be_placed(t));
}

BOOST_AUTO_TEST_CASE(can_be_placed_on_occupied_cell)
{
	board b;
	b(8, 11) = shape::J;

	auto t = tetrimino::from(shape::T);
	t.move({ 8, 11 });
	BOOST_TEST(!b.can_be_placed(t));
}


BOOST_AUTO_TEST_CASE(place_outside_board)
{
	board b;
	b(8, 11) = shape::J;

	auto t = tetrimino::from(shape::I);
	BOOST_CHECK_THROW(b.place(t), cannot_place_tetrimino_error);
}

BOOST_AUTO_TEST_CASE(place_on_free_space)
{
	board b;
	b(8, 11) = shape::J;

	auto t = tetrimino::from(shape::O);
	t.move({ 1, 1 });
	b.place(t);
	BOOST_TEST(b.free(1, 0));
	BOOST_TEST(b(1, 1) == t.tag());
	BOOST_TEST(b(1, 2) == t.tag());
	BOOST_TEST(b(2, 1) == t.tag());
	BOOST_TEST(b(2, 2) == t.tag());
	BOOST_TEST(b(8, 11) == shape::J);
}

BOOST_AUTO_TEST_CASE(place_on_occupied_cell)
{
	board b;
	b(8, 11) = shape::J;

	auto t = tetrimino::from(shape::T);
	t.move({ 8, 11 });
	BOOST_CHECK_THROW(b.place(t), cannot_place_tetrimino_error);
}

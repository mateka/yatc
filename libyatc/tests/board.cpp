#define BOOST_TEST_MODULE board
#include <boost/test/unit_test.hpp>

#include <yatc/board.h>
#include <yatc/shape.h>
#include <yatc/coordinate.h>
#include <yatc/tetriminos/tetriminos.h>
using namespace yatc;


BOOST_AUTO_TEST_CASE(constructor)
{
	const board b;
	BOOST_TEST(b.rows_count() == 20);
	BOOST_TEST(b.columns_count() == 10);
	BOOST_TEST(b.starting_pos() == coordinate(5, 20));
}

BOOST_AUTO_TEST_CASE(const_indexer)
{
	const board b;
	BOOST_TEST(b[coordinate(1, 9)] == shape::unknown);
}

BOOST_AUTO_TEST_CASE(indexer)
{
	board b;
	BOOST_TEST(b[coordinate(2, 0)] == shape::unknown);
	b[{8, 11}] = shape::J;
	BOOST_TEST(b[coordinate(8, 11)] == shape::J);
}

BOOST_AUTO_TEST_CASE(valid_x)
{
	board b;
	BOOST_TEST(!b.valid_x(-1));
	BOOST_TEST(b.valid_x(5));
	BOOST_TEST(!b.valid_x(b.columns_count()));
}

BOOST_AUTO_TEST_CASE(valid_y)
{
	board b;
	BOOST_TEST(!b.valid_y(-1));
	BOOST_TEST(b.valid_y(5));
	BOOST_TEST(!b.valid_y(b.rows_count()));
}

BOOST_AUTO_TEST_CASE(valid_extended_y)
{
	board b;
	BOOST_TEST(!b.valid_extended_y(-1));
	BOOST_TEST(b.valid_extended_y(5));
	BOOST_TEST(b.valid_extended_y(b.rows_count()));
	BOOST_TEST(!b.valid_extended_y(b.rows_count() + 4));
}

BOOST_AUTO_TEST_CASE(valid)
{
	board b;
	BOOST_TEST(!b.valid(coordinate(-1, 0)));
	BOOST_TEST(!b.valid(coordinate(0, -1)));
	BOOST_TEST(b.valid(coordinate(2, 0)));
	BOOST_TEST(!b.valid(coordinate(b.columns_count(), 0)));
	BOOST_TEST(!b.valid(coordinate(0, b.rows_count())));
}

BOOST_AUTO_TEST_CASE(free_cell)
{
	board b;
	BOOST_TEST(b.free(coordinate(8, 11)));
	b[{8, 11}]= shape::J;
	BOOST_TEST(b.free(coordinate(0, 0)));
	BOOST_TEST(!b.free(coordinate(8, 11)));
	BOOST_TEST(b.free(coordinate(8, 12)));
	BOOST_TEST(b.free(coordinate(7, 11)));
}

BOOST_AUTO_TEST_CASE(free_outside_board)
{
	board b;
	b[{8, 11}] = shape::J;

	tetrimino_i i;
	BOOST_TEST(!b.free(i));
}

BOOST_AUTO_TEST_CASE(free_free_space)
{
	board b;
	b[{8, 11}] = shape::J;

	tetrimino_o o;
	o.move({1, 1});
	BOOST_TEST(b.free(o));
}

BOOST_AUTO_TEST_CASE(free_starting_position)
{
	board b;
	b[{8, 11}] = shape::J;

	tetrimino_i i;
	i.move(b.starting_pos());
	BOOST_TEST(b.free(i));
}

BOOST_AUTO_TEST_CASE(free_occupied_cell)
{
	board b;
	b[{8, 11}] = shape::J;

	tetrimino_t t;
	t.move({ 8, 11 });
	BOOST_TEST(!b.free(t));
}

BOOST_AUTO_TEST_CASE(full_row)
{
	board b;
	const board::axis_type row = 10;
	for (board::axis_type i = 0; i < b.columns_count(); ++i)
		b[{i, row}] = shape::O;
	b[{8, 11}] = shape::J;
	BOOST_TEST(!b.full_row(11));
	BOOST_TEST(b.full_row(row));
	BOOST_TEST(!b.full_row(row - 1));
}

BOOST_AUTO_TEST_CASE(full)
{
	board b;
	b[{8, 11}] = shape::J;
	BOOST_TEST(!b.full());

	b[coordinate(8, b.rows_count() - 1)] = shape::O;
	BOOST_TEST(b.full());
}

BOOST_AUTO_TEST_CASE(can_be_placed_outside_board)
{
	board b;
	b[{8, 11}] = shape::J;

	tetrimino_i i;
	BOOST_TEST(!b.can_be_placed(i));
}

BOOST_AUTO_TEST_CASE(can_be_placed_free_space_without_support)
{
	board b;
	b[{8, 11}] = shape::J;

	tetrimino_o o;
	o.move({1, 1});
	BOOST_TEST(!b.can_be_placed(o));
}

BOOST_AUTO_TEST_CASE(can_be_placed_free_space_with_support)
{
	board b;
	b[{8, 8}] = shape::J;

	tetrimino_o o;
	o.move({7, 9});
	BOOST_TEST(b.can_be_placed(o));
}

BOOST_AUTO_TEST_CASE(can_be_placed_occupied_cell)
{
	board b;
	b[{8, 11}] = shape::J;

	tetrimino_t t;
	t.move({ 8, 11 });
	BOOST_TEST(!b.can_be_placed(t));
}

BOOST_AUTO_TEST_CASE(place_outside_board)
{
	board b;
	b[{8, 11}] = shape::J;

	tetrimino_i i;
	BOOST_CHECK_THROW(b.place(i), cannot_place_tetrimino_error);
}

BOOST_AUTO_TEST_CASE(place_on_free_space_with_support)
{
	board b;
	b[{8, 8}] = shape::J;

	tetrimino_o o;
	o.move({ 7, 9 });
	b.place(o);
	BOOST_TEST(b.free(coordinate(1, 0)));
	BOOST_TEST(b[coordinate(7, 9)] == o.tag());
	BOOST_TEST(b[coordinate(8, 9)] == o.tag());
	BOOST_TEST(b[coordinate(7, 10)] == o.tag());
	BOOST_TEST(b[coordinate(8, 10)] == o.tag());
	BOOST_TEST(b[coordinate(8, 8)] == shape::J);
}

BOOST_AUTO_TEST_CASE(place_on_free_space_without_support)
{
	board b;
	b[{8, 11}] = shape::J;

	tetrimino_o o;
	o.move({ 1, 1 });
	BOOST_CHECK_THROW(b.place(o), cannot_place_tetrimino_error);
}

BOOST_AUTO_TEST_CASE(place_on_occupied_cell)
{
	board b;
	b[{8, 11}] = shape::J;

	tetrimino_t t;
	t.move({ 8, 11 });
	BOOST_CHECK_THROW(b.place(t), cannot_place_tetrimino_error);
}

BOOST_AUTO_TEST_CASE(remove_not_full_row)
{
	board b;
	b[{8, 11}] = shape::J;
	BOOST_CHECK_THROW(b.remove_row(11), remove_not_full_row_error);
}

BOOST_AUTO_TEST_CASE(remove_row)
{
	board b;
	const board::axis_type row = 10;
	for(board::axis_type i = 0; i < b.columns_count(); ++i)
		b[{i, row}] = shape::O;
	b[{8, row + 1}] = shape::J;
	b[{3, row - 1}] = shape::L;
	b.remove_row(row);
	BOOST_TEST(b[coordinate(8, row)] == shape::J);
	BOOST_TEST(b[coordinate(3, row - 1)] == shape::L);
}

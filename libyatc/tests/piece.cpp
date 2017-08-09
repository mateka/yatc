#define BOOST_TEST_MODULE piece
#include <boost/test/unit_test.hpp>

#include <yatc/piece.h>
#include <yatc/board.h>
#include <yatc/direction.h>
#include <yatc/rotation.h>
#include <yatc/coordinate.h>
#include <yatc/tetriminos/tetriminos.h>

#include <memory>
#include <chrono>

using namespace yatc;
using namespace std::chrono;

BOOST_AUTO_TEST_CASE(constructor_with_empty_tetrimino)
{
    const coordinate pos{7, 13};
    BOOST_CHECK_THROW(piece(nullptr, pos, 1ns, 1ns), empty_tetrimino_error);
}

BOOST_AUTO_TEST_CASE(constructor)
{
    const coordinate pos{7, 13};
    tetrimino_i i;
    i.move(pos);
    const piece p{ std::make_unique<tetrimino_i>(), pos, 1ns, 1ns };

    // For some reason, boost does not like
    // reference to abstract base class
    const bool has_i_block = p.block() == i;
    BOOST_TEST(has_i_block);
    BOOST_TEST(p.position() == pos);
}

BOOST_AUTO_TEST_CASE(move_piece)
{
    const board b;
    const coordinate pos(b.columns_count() - 2, 10 );
    piece p{ std::make_unique<tetrimino_o>(), pos, 1ns, 1ns };
    p.move(b, direction::left);
    BOOST_TEST(p.position() == coordinate(pos.x() - 1, pos.y()));
}

BOOST_AUTO_TEST_CASE(move_piece_cooldown)
{
	const board b;
	const coordinate pos(b.columns_count() - 2, 10);
	piece p{ std::make_unique<tetrimino_o>(), pos, 1ns, 3600s };
	p.move(b, direction::left);
	p.move(b, direction::left);	// not executed because of cooldown
	BOOST_TEST(p.position() == coordinate(pos.x() - 1, pos.y()));
}

BOOST_AUTO_TEST_CASE(move_outside_board)
{
    const board b;
    const coordinate pos(b.columns_count() - 2, 10 );
    piece p{ std::make_unique<tetrimino_o>(), pos, 1ns, 1ns };
    p.move(b, direction::right);
    BOOST_TEST(p.position() == pos);
}

BOOST_AUTO_TEST_CASE(rotate_piece)
{
    const board b;
    const coordinate pos(b.columns_count() - 2, 10 );

    tetrimino_t expected_t;
    expected_t.rotate(rotation::cw);
    expected_t.move(pos);

    piece p{ std::make_unique<tetrimino_t>(), pos, 1ns, 1ns };
    p.rotate(b, rotation::cw);

    const auto block_are_equal = p.block() == expected_t;
    BOOST_TEST(block_are_equal);
}

BOOST_AUTO_TEST_CASE(rotate_piece_cooldown)
{
	const board b;
	const coordinate pos(b.columns_count() - 2, 10);

	tetrimino_t expected_t;
	expected_t.rotate(rotation::cw);
	expected_t.move(pos);

	piece p{ std::make_unique<tetrimino_t>(), pos, 1ns, 100s };
	p.rotate(b, rotation::cw);
	p.rotate(b, rotation::cw);	// not executed because of cooldown

	const auto block_are_equal = p.block() == expected_t;
	BOOST_TEST(block_are_equal);
}

BOOST_AUTO_TEST_CASE(rotate_outside_board)
{
    const board b;
    const coordinate pos(b.columns_count() - 1, 10 );

    tetrimino_i expected_i;
    expected_i.move(pos);

    piece p{ std::make_unique<tetrimino_i>(), pos, 1ns, 1ns };
    p.rotate(b, rotation::cw);

    const auto block_are_equal = p.block() == expected_i;
    BOOST_TEST(block_are_equal);
}

BOOST_AUTO_TEST_CASE(move_rotate_piece_cooldown)
{
	const board b;
	const coordinate pos(b.columns_count() - 2, 10);
	piece p{ std::make_unique<tetrimino_o>(), pos, 1ns, 3600s };
	p.move(b, direction::left);
	p.rotate(b, rotation::cw);	// not executed because of cooldown
	BOOST_TEST(p.position() == coordinate(pos.x() - 1, pos.y()));
}

BOOST_AUTO_TEST_CASE(can_be_placed_on_outside_board)
{
	const board b;
    piece p{ std::make_unique<tetrimino_i>(), {0, 0}, 1ns, 1ns };
	BOOST_TEST(!p.can_be_placed_on(b));
}

BOOST_AUTO_TEST_CASE(can_be_placed_on_free_space_without_support)
{
	board b;
	b[{8, 11}] = shape::J;

    piece p{ std::make_unique<tetrimino_o>(), {1, 1}, 1ns, 1ns };
	BOOST_TEST(!p.can_be_placed_on(b));
}

BOOST_AUTO_TEST_CASE(can_be_placed_on_free_space_with_support)
{
	board b;
	b[{8, 8}] = shape::J;

    piece p{ std::make_unique<tetrimino_o>(), {7, 9}, 1ns, 1ns };
	BOOST_TEST(p.can_be_placed_on(b));
}

BOOST_AUTO_TEST_CASE(can_be_placed_on_bottom)
{
	board b;
	b[{8, 8}] = shape::J;

	piece p{ std::make_unique<tetrimino_o>(),{ 6, 0 }, 1ns, 1ns };
	BOOST_TEST(p.can_be_placed_on(b));
}

BOOST_AUTO_TEST_CASE(can_be_placed_on_occupied_cell)
{
	board b;
	b[{8, 11}] = shape::J;

    piece p{ std::make_unique<tetrimino_t>(), {8, 11}, 1ns, 1ns };
	BOOST_TEST(!p.can_be_placed_on(b));
}

BOOST_AUTO_TEST_CASE(place_outside_board)
{
	board b;
	b[{8, 11}] = shape::J;

    piece p{ std::make_unique<tetrimino_i>(), {0, 0}, 1ns, 1ns };
	BOOST_CHECK_THROW(p.place_on(b), cannot_place_tetrimino_error);
}

BOOST_AUTO_TEST_CASE(place_on_free_space_with_support)
{
	board b;
	b[{8, 8}] = shape::J;

    piece p{ std::make_unique<tetrimino_o>(), {7, 9}, 1ns, 1ns };
	p.place_on(b);
	BOOST_TEST(b.free(coordinate(1, 0)));
	BOOST_TEST(b[coordinate(7, 9)] == p.block().tag());
	BOOST_TEST(b[coordinate(8, 9)] == p.block().tag());
	BOOST_TEST(b[coordinate(7, 10)] == p.block().tag());
	BOOST_TEST(b[coordinate(8, 10)] == p.block().tag());
	BOOST_TEST(b[coordinate(8, 8)] == shape::J);

	BOOST_TEST(p.position() == coordinate(-1, -1));
}

BOOST_AUTO_TEST_CASE(place_on_bottom)
{
	board b;
	b[{8, 8}] = shape::J;

	piece p{ std::make_unique<tetrimino_o>(),{ 4, 0 }, 1ns, 1ns };
	p.place_on(b);
	BOOST_TEST(b.free(coordinate(3, 0)));
	BOOST_TEST(b[coordinate(4, 0)] == p.block().tag());
	BOOST_TEST(b[coordinate(5, 0)] == p.block().tag());
	BOOST_TEST(b[coordinate(4, 1)] == p.block().tag());
	BOOST_TEST(b[coordinate(5, 1)] == p.block().tag());
	BOOST_TEST(b[coordinate(8, 8)] == shape::J);

	BOOST_TEST(p.position() == coordinate(-1, -1));
}

BOOST_AUTO_TEST_CASE(place_on_free_space_without_support)
{
	board b;
	b[{8, 11}] = shape::J;

    piece p{ std::make_unique<tetrimino_o>(), {1, 1}, 1ns, 1ns };
	BOOST_CHECK_THROW(p.place_on(b), cannot_place_tetrimino_error);
}

BOOST_AUTO_TEST_CASE(place_on_occupied_cell)
{
	board b;
	b[{8, 11}] = shape::J;

    piece p{ std::make_unique<tetrimino_t>(), {8, 11}, 1ns, 1ns };
	BOOST_CHECK_THROW(p.place_on(b), cannot_place_tetrimino_error);
}

BOOST_AUTO_TEST_CASE(update_piece)
{
	const board b;
	const coordinate pos(b.columns_count() - 2, 10);
	piece p{ std::make_unique<tetrimino_o>(), pos, 2s, 10ns };
	BOOST_TEST(p.position() == coordinate(pos.x(), pos.y()));
	p.update(1s);
	BOOST_TEST(p.position() == coordinate(pos.x(), pos.y() - 1));
	p.update(1s);
	BOOST_TEST(p.position() == coordinate(pos.x(), pos.y() - 1));
	p.update(1s);
	BOOST_TEST(p.position() == coordinate(pos.x(), pos.y() - 2));
}

BOOST_AUTO_TEST_CASE(update_piece_reduce_cooldown)
{
	const board b;
	const coordinate pos(b.columns_count() - 2, 10);
	piece p{ std::make_unique<tetrimino_o>(), pos, 3600s, 60s };
	p.move(b, direction::left);
	p.move(b, direction::left);	// not executed because of cooldown
	BOOST_TEST(p.position() == coordinate(pos.x() - 1, pos.y()));
	p.update(60s);
	p.move(b, direction::left);
	BOOST_TEST(p.position() == coordinate(pos.x() - 2, pos.y() - 1));
}

#pragma once

#include <yatc/shape.h>
#include <yatc/tetrimino.h>
#include <yatc/yatc_error.h>
#include <yatc/coordinate.h>

#include <array>
#include <vector>
#include <iostream>
#include <stdexcept>


namespace yatc {
/*! \brief Class for error of placing tetrimino in forbidden place on board. */
class cannot_place_tetrimino_error final : public yatc_error, public std::logic_error {
public:
	using logic_error::logic_error;
};

/*! \brief Class for error of removing not full row. */
class remove_not_full_row_error final : public yatc_error, public std::logic_error {
public:
	using logic_error::logic_error;
};


/*! \brief Class for tetris board.
*/
class board {
public:
	using type = shape;	//!< Type of single cell
	using axis_type = coordinate::type;	//!< Type of single axis coordinate
private:
	static constexpr axis_type m_rows_count = 20;	//!< how many rows is in board
	static constexpr axis_type m_columns_count = 10;	//!< how many columns is in board

	using row_type = std::array<shape, m_columns_count>;	//!< row contains 10 columns
	using tetrion_type = std::vector<row_type>;	//!< board consists of rows
public:
	/*! \brief Constructor creates empty board
	*/
	board();

	virtual ~board() {}

	/*!	\brief Rows count
	*	\return Count of rows in board
	*/
	axis_type rows_count() const;

	/*!	\brief Columns count
	*	\return Count of columns in board
	*/
	axis_type columns_count() const;

	/*! \brief Starting position for board.
	*   \return Coordinates of starting position.
	*/
	coordinate starting_pos() const;

	/*! \brief Indexing board by coordinates
	*   \param c cell's coordinates
	*   \return reference to cell from c.y() row and c.x() column.
	*/
	type& operator[](const coordinate c);

	/*! \brief Indexing board by coordinates
	*   \param c cell's coordinates
	*   \return Value of cell from c.y() row and c.x() column.
	*/
	type operator[](const coordinate c) const;

	/*! \brief Check if x coordinate is valid.
	*   \param x x coordinate
	*   \return true if x points to column on board.
	*/
	bool valid_x(const axis_type x) const;

	/*! \brief Check if y coordinate is valid.
	*   \param y y coordinate
	*   \return true if y points to row on board.
	*/
	bool valid_y(const axis_type y) const;

	/*! \brief Check if y coordinate is valid as an extended coordinate.
	*   \param y y coordinate
	*   \return true if y points to row on extended board (3 rows higher).
	*/
	bool valid_extended_y(const axis_type y) const;

	/*! \brief Check if coordinates are valid
	*   \param c coordinates to check
	*   \return true if point c is withing board's bounds.
	*/
	bool valid(const coordinate c) const;

	/*! \brief Tests whether given position is empty.
	*   \param c coordinates to check
	*	\return true if cell(c.x(), c.y()) is free.
	*/
	bool free(const coordinate c) const;

	/*! \brief Tests whether tetrimino's coordinates are empty.
	*   \param t tetrimino, which coordinates should be checked
	*	\return true if all tetrimino's coordinates are  free.
	*/
	bool free(const tetrimino& t) const;

	/*! \brief Tests whether given row has all columns occupied.
	*	\param row row index.
	*	\return true if all columns in row row are not free.
	*/
	bool full_row(const axis_type row) const;

	/*! \brief Tests whether tetrimino can be placed.
	*	\param t tetrimino to be placed.
	*	\return true if all cells from tetrimino coordinates are free
	*   and there is one cell occupied below tetrimino.
	*/
	bool can_be_placed(const tetrimino& t) const;

	/*! \brief Test whether board is full.
	*   \return true if board is full and game ended.
	*/
	virtual bool full() const;

	/*! \brief Place tetrimino on board.
	*	\param t tetrimino to be placed.
	*/
	void place(const tetrimino& t);

	/*! \brief Removes full row from board.
	*   \param row row index.
	*/
	virtual void remove_row(const axis_type row);
protected:
	row_type empty_row() const;	//!< Creates empty row
private:
	tetrion_type m_matrix;
};

/*! \brief Outputs board to output stream.
*  \param os output stream
*  \param b board
*  \return os stream with board b output to it.
*/
std::ostream& operator<<(std::ostream& os, const board& b);

}

#pragma once

#include <yatc/shape.h>
#include <yatc/tetrimino.h>
#include <yatc/yatc_error.h>

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


/*! \brief Class for tetris board.
*/
class board final {
public:
	using type = shape;	//!< Type of single cell
private:
	static constexpr std::size_t m_rows_count = 20;	//!< how many rows is in board
	static constexpr std::size_t m_columns_count = 10;	//!< how many columns is in board

	using row_type = std::array<shape, m_columns_count>;	//!< row contains 10 columns
	using tetrion_type = std::vector<row_type>;	//!< board consists of rows
public:
	/*! \brief Constructor creates empty board
	*/
	board();

	/*!	\brief Rows count
	*	\return Count of rows in board
	*/
	std::size_t rows_count() const;

	/*!	\brief Columns count
	*	\return Count of columns in board
	*/
	std::size_t columns_count() const;

	/*! \brief Single cell indexer.
	*	\param column column index.
	*	\param row row index.
	*	\return reference to cell from row row and column column.
	*/
	type& operator()(const std::size_t column, const std::size_t row);

	/*! \brief Single cell indexer.
	*	\param column column index.
	*	\param row row index.
	*	\return vaule of cell from row row and column column.
	*/
	type operator()(const std::size_t column, const std::size_t row) const;

	/*! \brief Tests whether given position is empty.
	*	\param column column index.
	*	\param row row index.
	*	\return true if cells(column, row) is free.
	*/
	bool free(const std::size_t column, const std::size_t row) const;

	/*! \brief Tests whether given row has all columns occupied.
	*	\param row row index.
	*	\return true if all columns in row row are not free.
	*/
	bool full(const std::size_t row) const;

	/*! \brief Tests whether tetrimino can be placed.
	*	\param t tetrimino to be placed.
	*	\return true if all cells from tetrimino coordinates are free.
	*/
	bool can_be_placed(const tetrimino& t) const;

	/*! \brief Place tetrimino on board.
	*	\param t tetrimino to be placed.
	*/
	void place(const tetrimino& t);
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

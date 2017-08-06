#pragma once

#include <yatc/coordinate.h>
#include <yatc/rotation.h>
#include <yatc/shape.h>
#include <yatc/yatc_error.h>

#include <array>
#include <stdexcept>


namespace yatc {
/*! \brief Class for error of creating tetrimino from wrong shape. */
class unknown_shape_error final : public yatc_error, public std::logic_error {
public:
	using logic_error::logic_error;
};


/*! \brief Represents one tetrimino.
*/
class tetrimino final {
	using container = std::array<coordinate, 4>;
public:
	using const_iterator = container::const_iterator;	//!< const iterator to piece

	/*! \brief Creates tetrimino of given shape
	*	\param s new tetrimino shape
	*	\return New tetrimino of shape s.
	*/
	static tetrimino from(const shape s);

	/*! \brief Creates tetrimino from four coordinates
	*	\param a first piece
	*	\param b second piece
	*	\param c third piece
	*	\param d fourth piece
	*	\param s shape tag (default: unknown)
	*/
	tetrimino(
		const coordinate a, const coordinate b,
		const coordinate c, const coordinate d,
		const shape s = shape::unknown
	);

	tetrimino(tetrimino&&) = default;
	tetrimino(const tetrimino&) = default;
	tetrimino& operator=(tetrimino&&) = default;
	tetrimino& operator=(const tetrimino&) = default;

	/*! \brief begin of shape
	*	\return iterator to first, const piece
	*/
	const_iterator begin() const;
	const_iterator cbegin() const;

	/*! \brief end of shape
	*	\return iterator past last, const piece
	*/
	const_iterator end() const;
	const_iterator cend() const;

	/*! \brief shape tag accessor
	*	\return shape tag for this tetrimino
	*/
	shape tag() const;

	/*! \brief Moves tetrimino by vector.
	*  \param c translation vector.
	*/
	void move(const coordinate c);

	/*! \brief Rotates tetrimino for 90deg around {0, 0}.
	*  \param d direction of rotation.
	*/
	void rotate(const rotation d);
private:
	container m_pieces;
	shape m_tag;
};

/*! \brief Comprison.
*  \param a first tetrimino
*  \param b second tetrimino
*  \return true if all a tetrimino's coordinates are equal
*  to b tetrimino's coordinates.
*/
bool operator==(const tetrimino& a, const tetrimino& b);

/*! \brief Comprison.
*  \param a first tetrimino
*  \param b second tetrimino
*  \return true if not all a tetrimino's coordinates are equal
*  to b tetrimino's coordinates.
*/
bool operator!=(const tetrimino& a, const tetrimino& b);

/*! \brief Moves tetrimino by vector.
*	\param t tetrimino to transform.
*	\param c translation vector.
*	\return Tetrimino t moved by vector c.
*/
tetrimino move(tetrimino t, const coordinate c);

/*! \brief Rotates tetrimino by 90deg around {0, 0}.
*	\param t tetrimino to transform.
*	\param d direction of rotation.
*	\return Tetrimino t rotated by 90deg in direction d.
*/
tetrimino rotate(tetrimino t, const rotation d);

/*! \brief Outputs tetrimino to output stream.
*  \param os output stream
*  \param t tetrimino
*  \return os stream with tetrimino t output to it.
*/
std::ostream& operator<<(std::ostream& os, const tetrimino& t);

}

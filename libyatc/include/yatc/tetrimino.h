#pragma once

#include <yatc/coordinate.h>
#include <yatc/rotation.h>
#include <yatc/shape.h>
//#include <yatc/yatc_error.h>

#include <array>
#include <algorithm>
//#include <stdexcept>


namespace yatc {
// /*! \brief Class for error of creating tetrimino from wrong shape. */
// class unknown_shape_error final : public yatc_error, public std::logic_error {
// public:
// 	using logic_error::logic_error;
// };


/*! \brief Interface for one tetrimino.
*/
class tetrimino {
public:
	using container = std::array<coordinate, 4>;
	using const_iterator = container::const_iterator;	//!< iterator to const piece

	/*! \brief Creates tetrimino of given shape
	*	\param s new tetrimino shape
	*	\return New tetrimino of shape s.
	*/
	// static tetrimino from(const shape s);

	tetrimino() = default;
	virtual ~tetrimino() {}

	tetrimino(tetrimino&&) = delete;
	tetrimino(const tetrimino&) = delete;
	tetrimino& operator=(tetrimino&&) = delete;
	tetrimino& operator=(const tetrimino&) = delete;

	/*! \brief begin of tetrimino
	*	\return iterator to first, const piece
	*/
	virtual const_iterator begin() const = 0;

	/*! \brief begin of tetrimino
	*	\return iterator to first, const piece
	*/
	virtual const_iterator cbegin() const = 0;

	/*! \brief end of tetrimino
	*	\return iterator past last, const piece
	*/
	virtual const_iterator end() const = 0;

	/*! \brief end of tetrimino
	*	\return iterator past last, const piece
	*/
	virtual const_iterator cend() const = 0;

	/*! \brief shape tag accessor
	*	\return shape tag for this tetrimino
	*/
	virtual shape tag() const = 0;

	/*! \brief Moves tetrimino by vector.
	*  \param c translation vector.
	*/
	virtual void move(const coordinate c) = 0;

	/*! \brief Rotates tetrimino for 90deg around {0, 0}.
	*  \param d direction of rotation.
	*/
	virtual void rotate(const rotation d) = 0;
};

/*! \brief Comprison.
*  \param a first tetrimino
*  \param b second tetrimino
*  \return true if all a tetrimino's coordinates are equal
*  to b tetrimino's coordinates.
*/
inline bool operator==(const tetrimino& a, const tetrimino& b) {
	if (a.tag() != shape::unknown || b.tag() != shape::unknown)
	{
		if (a.tag() != b.tag())
			return false;
	}
	return std::equal(std::cbegin(a), std::cend(a), std::cbegin(b));
}

/*! \brief Comprison.
*  \param a first tetrimino
*  \param b second tetrimino
*  \return true if not all a tetrimino's coordinates are equal
*  to b tetrimino's coordinates.
*/
inline bool operator!=(const tetrimino& a, const tetrimino& b) {
	return !(a == b);
}

/*! \brief Outputs tetrimino to output stream.
*  \param os output stream
*  \param t tetrimino
*  \return os stream with tetrimino t output to it.
*/
inline std::ostream& operator<<(std::ostream& os, const tetrimino& t) {
	os << t.tag() << " [";
	std::for_each(
		std::cbegin(t), std::cend(t),
		[&os](const coordinate c) { os << c << ", "; }
	);
	return os << "]";
}

}

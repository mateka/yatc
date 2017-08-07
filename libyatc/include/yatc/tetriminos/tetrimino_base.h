#pragma once

#include <yatc/coordinate.h>
#include <yatc/rotation.h>
#include <yatc/shape.h>
#include <yatc/tetrimino.h>

#include <array>


namespace yatc {

/*! \brief Base class for classes representing one tetrimino.
*/
class tetrimino_base : public tetrimino {
public:
	/*! \brief Creates tetrimino from four coordinates
	*	\param a first piece
	*	\param b second piece
	*	\param c third piece
	*	\param d fourth piece
	*	\param s shape tag (default: unknown)
	*/
	tetrimino_base(
		const coordinate a, const coordinate b,
		const coordinate c, const coordinate d,
		const shape s = shape::unknown
	);
	/*! \brief begin of tetrimino
	*	\return iterator to first, const piece
	*/
	const_iterator begin() const override;

	/*! \brief begin of tetrimino
	*	\return iterator to first, const piece
	*/
	const_iterator cbegin() const override;

	/*! \brief end of tetrimino
	*	\return iterator past last, const piece
	*/
	const_iterator end() const override;

	/*! \brief end of tetrimino
	*	\return iterator past last, const piece
	*/
	const_iterator cend() const override;

	/*! \brief shape tag accessor
	*	\return shape tag for this tetrimino
	*/
	shape tag() const override;

	/*! \brief Moves tetrimino by vector.
	*  \param c translation vector.
	*/
	void move(const coordinate c) override;

	/*! \brief Rotates tetrimino for 90deg around {0, 0}.
	*  \param d direction of rotation.
	*/
	void rotate(const rotation d) override;
protected:
	using iterator = container::iterator;	//!< iterator to const piece

	/*! \brief begin of tetrimino
	*	\return iterator to first piece
	*/
	iterator begin();

	/*! \brief end of tetrimino
	*	\return iterator past last piece
	*/
	iterator end();
private:
	container m_pieces;
	shape m_tag;
};

}

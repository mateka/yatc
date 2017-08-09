#pragma once

#include <yatc/tetrimino.h>

#include <memory>


namespace yatc {
/*! \brief Interface for tetrimino factories.
*
*/
class tetrimino_factory {
public:
	using type = std::unique_ptr<tetrimino>;	//!< Type of handle to tetrimino

	virtual ~tetrimino_factory() {}

	/*! \brief Creates new tetrimino.
	*	\return Handle to newly created tetrimino.
	*/
	virtual type next() = 0;
};

}

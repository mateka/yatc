#pragma once

#include <yatc/tetriminos/tetrimino_base.h>
#include <yatc/rotation.h>


namespace yatc {

/*! \brief Class representing o tetrimino.
*/
class tetrimino_o : public tetrimino_base {
public:
    /*! \brief Creates o tetrimino. */
    tetrimino_o();

    /*! \brief Rotates tetrimino for 90deg around {0, 0}.
	*   \param d direction of rotation.
    *   \remarks Tetrimino o does not rotate, so this method is no-op.
	*/
	void rotate(const rotation d) override;
};

}

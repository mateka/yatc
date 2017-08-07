#pragma once

#include <yatc/tetriminos/tetrimino_base.h>
#include <yatc/rotation.h>



namespace yatc {

/*! \brief Class representing i tetrimino.
*/
class tetrimino_i : public tetrimino_base {
public:
    /*! \brief Creates i tetrimino. */
    tetrimino_i();

    /*! \brief Rotates tetrimino for 90deg around {0, 0}.
	*   \param d direction of rotation.
    *   \remarks Tetrimino i can only rotate between vertical and horizontal positions.
	*/
	void rotate(const rotation d) override;
private:
    bool m_rotated;
};

}

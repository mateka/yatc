#include <yatc/tetriminos/tetrimino_i.h>
#include <yatc/coordinate.h>
#include <yatc/shape.h>


namespace yatc {

tetrimino_i::tetrimino_i()
    : tetrimino_base{
        coordinate{ 0, -1 }, coordinate{ 0, 0 },
        coordinate{ 0, 1 }, coordinate{ 0, 2 },
        shape::I
    }, m_rotated{false}
{}

void tetrimino_i::rotate(const rotation d) {
    if(!m_rotated)
        tetrimino_base::rotate(rotation::ccw);
    else
        tetrimino_base::rotate(rotation::cw);
    m_rotated = !m_rotated;
}

}

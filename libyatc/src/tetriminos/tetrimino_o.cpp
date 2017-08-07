#include <yatc/tetriminos/tetrimino_o.h>
#include <yatc/coordinate.h>
#include <yatc/shape.h>


namespace yatc {

tetrimino_o::tetrimino_o()
    : tetrimino_base{
        coordinate{ 0, 0 }, coordinate{ 1, 0 },
        coordinate{ 0, 1 }, coordinate{ 1, 1 },
        shape::O
    }
{}

void tetrimino_o::rotate(const rotation /*d*/) {}

}

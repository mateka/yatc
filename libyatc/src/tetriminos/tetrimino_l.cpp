#include <yatc/tetriminos/tetrimino_l.h>
#include <yatc/coordinate.h>
#include <yatc/shape.h>


namespace yatc {

tetrimino_l::tetrimino_l()
    : tetrimino_base{
        coordinate{ 0, -1 }, coordinate{ 0, 0 },
        coordinate{ 0, 1 }, coordinate{ 1, 1 },
        shape::L
    }
{}

}

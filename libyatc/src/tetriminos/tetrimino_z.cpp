#include <yatc/tetriminos/tetrimino_z.h>
#include <yatc/coordinate.h>
#include <yatc/shape.h>


namespace yatc {

tetrimino_z::tetrimino_z()
    : tetrimino_base{
        coordinate{ -1, 0 }, coordinate{ 0, 0 },
        coordinate{ 0, 1 }, coordinate{ 1, 1 },
        shape::Z
    }
{}

}

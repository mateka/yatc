#include <yatc/tetriminos/tetrimino_s.h>
#include <yatc/coordinate.h>
#include <yatc/shape.h>


namespace yatc {

tetrimino_s::tetrimino_s()
    : tetrimino_base{
        coordinate{ 0, 0 }, coordinate{ 1, 0 },
        coordinate{ -1, 1 }, coordinate{ 0, 1 },
        shape::S
    }
{}

}

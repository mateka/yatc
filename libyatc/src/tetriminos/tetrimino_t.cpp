#include <yatc/tetriminos/tetrimino_t.h>
#include <yatc/coordinate.h>
#include <yatc/shape.h>


namespace yatc {

tetrimino_t::tetrimino_t()
    : tetrimino_base{
        coordinate{ -1, 0 }, coordinate{ 0, 0 },
        coordinate{ 1, 0 }, coordinate{ 0, 1 },
        shape::T
    }
{}

}

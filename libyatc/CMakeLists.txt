
set(TARGET libyatc)
set(SRCS
    src/coordinate.cpp
    src/cooldown_timer.cpp
    src/board.cpp
    src/piece.cpp
    src/tetriminos/tetrimino_base.cpp
    src/tetriminos/tetrimino_i.cpp
    src/tetriminos/tetrimino_j.cpp
    src/tetriminos/tetrimino_l.cpp
    src/tetriminos/tetrimino_o.cpp
    src/tetriminos/tetrimino_s.cpp
    src/tetriminos/tetrimino_t.cpp
    src/tetriminos/tetrimino_z.cpp
)

add_library(${TARGET} STATIC ${SRCS})
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(tests)

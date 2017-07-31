
set(TARGET libyatc)
set(SRCS
    src/coordinate.cpp
)

add_library(${TARGET} STATIC ${SRCS})
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(tests)


set(TARGET yatc)

add_executable(${TARGET} main.cpp)
target_link_libraries(${TARGET} libyatc)

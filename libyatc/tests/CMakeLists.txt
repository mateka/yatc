add_definitions(-DBOOST_TEST_DYN_LINK) 

add_executable(coordinate coordinate.cpp)
target_link_libraries(coordinate libyatc ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME coordinate COMMAND coordinate)

add_executable(cooldown_timer cooldown_timer.cpp)
target_link_libraries(cooldown_timer libyatc ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME cooldown_timer COMMAND cooldown_timer)

add_executable(tetrimino tetrimino.cpp)
target_link_libraries(tetrimino libyatc ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME tetrimino COMMAND tetrimino)

add_executable(board board.cpp)
target_link_libraries(board libyatc ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME board COMMAND board)

add_executable(uniform_tetrimino_factory uniform_tetrimino_factory.cpp)
target_link_libraries(uniform_tetrimino_factory libyatc ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME uniform_tetrimino_factory COMMAND uniform_tetrimino_factory)

add_executable(piece piece.cpp)
target_link_libraries(piece libyatc ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME piece COMMAND piece)

add_subdirectory(tetriminos)

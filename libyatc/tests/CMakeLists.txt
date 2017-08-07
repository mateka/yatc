add_definitions(-DBOOST_TEST_DYN_LINK) 

add_executable(coordinate coordinate.cpp)
target_link_libraries(coordinate libyatc ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME coordinate COMMAND coordinate)

add_executable(tetrimino tetrimino.cpp)
target_link_libraries(tetrimino libyatc ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME tetrimino COMMAND tetrimino)

add_executable(board board.cpp)
target_link_libraries(board libyatc ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME board COMMAND board)

add_subdirectory(tetriminos)

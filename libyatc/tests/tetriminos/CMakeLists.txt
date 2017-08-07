add_definitions(-DBOOST_TEST_DYN_LINK) 

add_executable(tetrimino_base tetrimino_base.cpp)
target_link_libraries(tetrimino_base libyatc ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME tetrimino_base COMMAND tetrimino_base)

add_executable(tetrimino_i tetrimino_i.cpp)
target_link_libraries(tetrimino_i libyatc ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME tetrimino_i COMMAND tetrimino_i)

add_executable(tetrimino_j tetrimino_j.cpp)
target_link_libraries(tetrimino_j libyatc ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME tetrimino_j COMMAND tetrimino_j)

add_executable(tetrimino_l tetrimino_l.cpp)
target_link_libraries(tetrimino_l libyatc ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME tetrimino_l COMMAND tetrimino_l)

add_executable(tetrimino_o tetrimino_o.cpp)
target_link_libraries(tetrimino_o libyatc ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME tetrimino_o COMMAND tetrimino_o)

add_executable(tetrimino_s tetrimino_s.cpp)
target_link_libraries(tetrimino_s libyatc ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME tetrimino_s COMMAND tetrimino_s)

add_executable(tetrimino_t tetrimino_t.cpp)
target_link_libraries(tetrimino_t libyatc ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME tetrimino_t COMMAND tetrimino_t)

add_executable(tetrimino_z tetrimino_z.cpp)
target_link_libraries(tetrimino_z libyatc ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME tetrimino_z COMMAND tetrimino_z)

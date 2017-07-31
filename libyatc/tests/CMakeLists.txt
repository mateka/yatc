add_definitions(-DBOOST_TEST_DYN_LINK) 

add_executable(coordinate coordinate.cpp)
target_link_libraries(coordinate libyatc ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
#target_link_libraries(coordinate libyatc Boost::unit_test_framework)
add_test(NAME coordinate COMMAND coordinate)

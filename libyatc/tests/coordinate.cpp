#define BOOST_TEST_MODULE coordinate
#include <boost/test/unit_test.hpp>

#include <yatc/coordinate.h>
using namespace yatc;

BOOST_AUTO_TEST_CASE(default_constructor)
{
    coordinate zero;
    BOOST_TEST(zero.x() == 0);
    BOOST_TEST(zero.y() == 0);
}

BOOST_AUTO_TEST_CASE(default_constructor_const)
{
    const coordinate zero;
    BOOST_TEST(zero.x() == 0);
    BOOST_TEST(zero.y() == 0);
}

BOOST_AUTO_TEST_CASE(constructor)
{
    coordinate pt {1, 3};
    BOOST_TEST(pt.x() == 1);
    BOOST_TEST(pt.y() == 3);
}

BOOST_AUTO_TEST_CASE(const_accessors)
{
    const coordinate pt {4, 2};
    BOOST_TEST(pt.x() == 4);
    BOOST_TEST(pt.y() == 2);
}

BOOST_AUTO_TEST_CASE(x)
{
    coordinate pt {1, 3};
    BOOST_TEST(pt.x() == 1);
    pt.x() = -10;
    BOOST_TEST(pt.x() == -10);
}

BOOST_AUTO_TEST_CASE(y)
{
    coordinate pt {1, 3};
    BOOST_TEST(pt.y() == 3);
    pt.y() = -13;
    BOOST_TEST(pt.y() == -13);
}

BOOST_AUTO_TEST_CASE(plus_equal)
{
    coordinate pt {-3, 2};
    pt += coordinate(1, 3);
    BOOST_TEST(pt == coordinate(-2, 5));
}

BOOST_AUTO_TEST_CASE(minus_equal)
{
    coordinate pt {-3, 2};
    pt -= coordinate(3, 1);
    BOOST_TEST(pt == coordinate(-6, 1));
}

BOOST_AUTO_TEST_CASE(ccw_rotate)
{
    coordinate pt {5, 0};
    pt.rotate(rotation::ccw);
    BOOST_TEST(pt == coordinate(0, 5));
}

BOOST_AUTO_TEST_CASE(cw_rotate)
{
    coordinate pt {0, -5};
    pt.rotate(rotation::cw);
    BOOST_TEST(pt == coordinate(-5, 0));
}

BOOST_AUTO_TEST_CASE(unary_minus)
{
    coordinate pt {-3, 2};
    BOOST_TEST(-pt == coordinate(3, -2));
}

BOOST_AUTO_TEST_CASE(plus)
{
    coordinate pt {-3, 2};
    coordinate v(1, 3);
    BOOST_TEST((pt + v) == coordinate(-2, 5));
}

BOOST_AUTO_TEST_CASE(minus)
{
    coordinate pt {-3, 2};
    coordinate v(3, 1);
    BOOST_TEST((pt - v) == coordinate(-6, 1));
}

BOOST_AUTO_TEST_CASE(equal)
{
    coordinate pt1 {1, 3};
    coordinate pt2 {1, 3};
    BOOST_TEST(pt1 == pt2);
}

BOOST_AUTO_TEST_CASE(not_equal)
{
    coordinate pt1 {1, 3};
    coordinate pt2 {3, 1};
    BOOST_TEST(pt1 != pt2);
}

BOOST_AUTO_TEST_CASE(ccw_rotate_copy)
{
    coordinate pt {3, 1};
    BOOST_TEST(rotate(pt, rotation::ccw) == coordinate(-1, 3));
}

BOOST_AUTO_TEST_CASE(cw_rotate_copy)
{
    coordinate pt {3, -4};
    BOOST_TEST(rotate(pt, rotation::cw) == coordinate(-4, -3));
}

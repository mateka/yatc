#define BOOST_TEST_MODULE cooldown_timer
#include <boost/test/unit_test.hpp>

#include <yatc/cooldown_timer.h>

using namespace yatc;
using namespace std::chrono;


BOOST_AUTO_TEST_CASE(constructor)
{
    cooldown_timer timer(1s);
    const auto remaining_is_0_s = timer.remaining() == 0s;
    const auto cooldown_is_1_s = timer.cooldown() == 1s;
    BOOST_TEST(remaining_is_0_s);
    BOOST_TEST(cooldown_is_1_s);
    BOOST_TEST(static_cast<bool>(timer));
}

BOOST_AUTO_TEST_CASE(execute)
{
    cooldown_timer timer(1s);
    BOOST_TEST(timer.execute([]() { std::cout << "Executed" << std::endl; }));
    const auto remaining_is_1_s = timer.remaining() == 1s;
    BOOST_TEST(remaining_is_1_s);
    BOOST_TEST(!timer.execute([]() { std::cout << "Not executed" << std::endl; }));
}

BOOST_AUTO_TEST_CASE(execute_update)
{
    cooldown_timer timer(1s);
    BOOST_TEST(timer.execute([]() { std::cout << "Executed" << std::endl; }));

    timer.update(500ms);
    const auto remaining_is_500_ms = timer.remaining() == 500ms;
    BOOST_TEST(remaining_is_500_ms);
    BOOST_TEST(!timer.execute([]() { std::cout << "Not executed" << std::endl; }));

    timer.update(500ms);
    const auto remaining_is_0_s = timer.remaining() == 0s;
    BOOST_TEST(remaining_is_0_s);
    BOOST_TEST(timer.execute([]() { std::cout << "Executed" << std::endl; }));
}

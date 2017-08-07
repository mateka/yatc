#define BOOST_TEST_MODULE tetrimino
#include <boost/test/unit_test.hpp>

#include <yatc/coordinate.h>
#include <yatc/tetrimino.h>
#include <yatc/shape.h>

#include <memory>

using namespace yatc;


class impl : public tetrimino {
public:
	impl(
		const coordinate a,
		const coordinate b,
		const coordinate c,
		const coordinate d,
		const shape s = shape::unknown
	) : m_data{ a, b, c, d }, m_tag{ s }
	{}

	const_iterator begin() const override {
		return std::begin(m_data);
	}

	const_iterator cbegin() const override {
		return std::cbegin(m_data);
	}

	const_iterator end() const override {
		return std::end(m_data);
	}

	const_iterator cend() const override {
		return std::cend(m_data);
	}

	shape tag() const override {
		return m_tag;
	}

	void move(const coordinate c) override {}

	void rotate(const rotation d) override {}
private:
	container m_data;
	shape m_tag;
};

BOOST_AUTO_TEST_CASE(equality)
{
	const impl l(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }
	);
	const impl other_l(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }
	);
	BOOST_TEST(l == other_l);
}

BOOST_AUTO_TEST_CASE(equality_with_tag)
{
	impl l(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }, shape::L
	);
	impl other_l(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }, shape::L
	);
	BOOST_TEST(l == other_l);
}

BOOST_AUTO_TEST_CASE(inequality)
{
	const impl l(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }
	);
	impl t(
		coordinate{ -1, 0 }, coordinate{ 0, 0 },
		coordinate{ 1, 0 }, coordinate{ 0, 1 }
	);
	BOOST_TEST(l != t);
}

BOOST_AUTO_TEST_CASE(inequality_with_tag)
{
	impl l(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }, shape::L
	);
	const impl other(
		coordinate{ 0, -1 }, coordinate{ 0, 0 },
		coordinate{ 0, 1 }, coordinate{ 1, 1 }, shape::T
	);
	BOOST_TEST(l != other);
}

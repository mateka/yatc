#include <yatc/uniform_tetrimino_factory.h>
#include <yatc/tetriminos/tetriminos.h>
#include <yatc/rotation.h>


namespace yatc {

namespace {

template<typename TetriminoType>
uniform_tetrimino_factory::creator make_creator(const std::size_t rotations) {
	return [rotations]() {
		auto result = std::make_unique<TetriminoType>();
		for (std::size_t i = 0; i < rotations; ++i)
			result->rotate(rotation::cw);
		return result;
	};
}

}

uniform_tetrimino_factory::uniform_tetrimino_factory(const std::mt19937_64::result_type seed)
	: m_factories{
		make_creator<tetrimino_i>(0),
		make_creator<tetrimino_i>(1),
		make_creator<tetrimino_j>(0),
		make_creator<tetrimino_j>(1),
		make_creator<tetrimino_j>(2),
		make_creator<tetrimino_j>(3),
		make_creator<tetrimino_l>(0),
		make_creator<tetrimino_l>(1),
		make_creator<tetrimino_l>(2),
		make_creator<tetrimino_l>(3),
		make_creator<tetrimino_o>(0),
		make_creator<tetrimino_s>(0),
		make_creator<tetrimino_s>(1),
		make_creator<tetrimino_t>(0),
		make_creator<tetrimino_t>(1),
		make_creator<tetrimino_t>(2),
		make_creator<tetrimino_t>(3),
		make_creator<tetrimino_z>(0),
		make_creator<tetrimino_z>(1)
	},
	m_random_engine(seed),
	m_distribution(0, m_factories.size() - 1)
{}

uniform_tetrimino_factory::type uniform_tetrimino_factory::next() {
	return m_factories[m_distribution(m_random_engine)]();
}

}

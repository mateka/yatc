#pragma once

#include <yatc/tetrimino_factory.h>
#include <yatc/tetrimino.h>

#include <array>
#include <memory>
#include <random>
#include <functional>


namespace yatc {
/*! \brief Interface for tetrimino factories.
*
*/
class uniform_tetrimino_factory : public tetrimino_factory {
public:
	using creator = std::function<type()>;	//!< Type for function creating tetrimino

	/*! \brief Creates factory, which returns all combinations of tetriminos
	*	and their rotations with equal probabilities.
	*	\param seed seed for random engine
	*/
	uniform_tetrimino_factory(const std::mt19937_64::result_type seed);

	/*! \brief Creates new tetrimino.
	*	\return Handle to newly created tetrimino.
	*/
	type next() override;
private:
	std::array<creator, 19>	m_factories;
	std::mt19937_64 m_random_engine;
	std::uniform_int_distribution<> m_distribution;
};

}

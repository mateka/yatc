#include <yatc/tetriminos/tetrimino_base.h>
#include <algorithm>
#include <sstream>


namespace yatc {

tetrimino_base::tetrimino_base(
	const coordinate a,
	const coordinate b,
	const coordinate c,
	const coordinate d,
	const shape s
) : m_pieces{ a, b, c, d }, m_tag{ s }
{}

tetrimino_base::const_iterator tetrimino_base::begin() const {
	return std::begin(m_pieces);
}

tetrimino_base::const_iterator tetrimino_base::cbegin() const {
	return std::cbegin(m_pieces);
}

tetrimino_base::const_iterator tetrimino_base::end() const {
	return std::end(m_pieces);
}

tetrimino_base::const_iterator tetrimino_base::cend() const {
	return std::cend(m_pieces);
}

shape tetrimino_base::tag() const {
	return m_tag;
}

void tetrimino_base::move(const coordinate c) {
	for (auto& piece : m_pieces)
		piece += c;
}

void tetrimino_base::rotate(const rotation d) {
	for (auto& piece : m_pieces)
		piece.rotate(d);
}

tetrimino_base::iterator tetrimino_base::begin() {
	return std::begin(m_pieces); 
}

tetrimino_base::iterator tetrimino_base::end() {
	return std::end(m_pieces); 
}

}

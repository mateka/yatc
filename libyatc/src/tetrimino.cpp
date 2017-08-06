#include <yatc/tetrimino.h>
#include <algorithm>
#include <sstream>


namespace yatc {

tetrimino tetrimino::from(const shape s) {
	switch (s)
	{
	case shape::I:
		return { coordinate{ 0, -1 }, coordinate{ 0, 0 }, coordinate{ 0, 1 }, coordinate{ 0, 2 }, s };
	case shape::J:
		return { coordinate{ 0, -1 }, coordinate{ 0, 0 }, coordinate{ 0, 1 }, coordinate{ -1, 1 }, s };
	case shape::L:
		return { coordinate{ 0, -1 }, coordinate{ 0, 0 }, coordinate{ 0, 1 }, coordinate{ 1, 1 }, s };
	case shape::O:
		return { coordinate{ 0, 0 }, coordinate{ 1, 0 }, coordinate{ 0, 1 }, coordinate{ 1, 1 }, s };
	case shape::S:
		return { coordinate{ 1, 0 }, coordinate{ 2, 0 }, coordinate{ 0, 1 }, coordinate{ 1, 1 }, s };
	case shape::Z:
		return { coordinate{ -1, 0 }, coordinate{ 0, 0 }, coordinate{ 0, 1 }, coordinate{ 1, 1 }, s };
	case shape::T:
		return { coordinate{ -1, 0 }, coordinate{ 0, 0 }, coordinate{ 1, 0 }, coordinate{ 0, 1 }, s };
	default:
		std::ostringstream msg;
		msg << "Unknown shape '" << s << "'!";
		throw unknown_shape_error(msg.str());
	}
}


tetrimino::tetrimino(
	const coordinate a,
	const coordinate b,
	const coordinate c,
	const coordinate d,
	const shape s
) : m_pieces{ a, b, c, d }, m_tag{ s }
{}

tetrimino::const_iterator tetrimino::begin() const {
	return std::begin(m_pieces);
}

tetrimino::const_iterator tetrimino::cbegin() const {
	return std::cbegin(m_pieces);
}

tetrimino::const_iterator tetrimino::end() const {
	return std::end(m_pieces);
}

tetrimino::const_iterator tetrimino::cend() const {
	return std::cend(m_pieces);
}

shape tetrimino::tag() const {
	return m_tag;
}

void tetrimino::move(const coordinate c) {
	for (auto& piece : m_pieces)
		piece += c;
}

void tetrimino::rotate(const rotation d) {
	for (auto& piece : m_pieces)
		piece.rotate(d);
}

bool operator==(const tetrimino& a, const tetrimino& b) {
	if (a.tag() != shape::unknown || b.tag() != shape::unknown)
	{
		if (a.tag() != b.tag())
			return false;
	}
	return std::equal(std::cbegin(a), std::cend(a), std::cbegin(b));
}

bool operator!=(const tetrimino& a, const tetrimino& b) {
	return !(a == b);
}

tetrimino move(tetrimino t, const coordinate c) {
	t.move(c);
	return t;
}

tetrimino rotate(tetrimino t, const rotation d) {
	t.rotate(d);
	return t;
}

std::ostream& operator<<(std::ostream& os, const tetrimino& t) {
	os << t.tag() << " [";
	std::for_each(
		std::cbegin(t), std::cend(t),
		[&os](const coordinate c) { os << c << ", "; }
	);
	return os << "]";
}

}

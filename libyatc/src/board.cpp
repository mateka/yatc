#include <yatc/board.h>
#include <algorithm>
#include <sstream>


namespace yatc {

board::board()
	: m_matrix(
		m_rows_count,
		[]() { row_type r; r.fill(shape::unknown); return r; }()
	)
{}

std::size_t board::rows_count() const {
	return m_rows_count;
}

std::size_t board::columns_count() const {
	return m_columns_count;
}

board::type& board::operator()(const std::size_t column, const std::size_t row) {
	return m_matrix[row][column];
}

board::type board::operator()(const std::size_t column, const std::size_t row) const {
	return m_matrix[row][column];
}

bool board::free(const std::size_t column, const std::size_t row) const {
	return (*this)(column, row) == shape::unknown;
}

bool board::full(const std::size_t row) const {
	const auto& row_data = m_matrix[row];
	return std::all_of(
		std::cbegin(row_data), std::cend(row_data),
		[](const auto c) { return c != shape::unknown; }
	);
}

bool board::can_be_placed(const tetrimino& t) const {
	return std::all_of(
		std::cbegin(t), std::cend(t), [this](auto c) {
		return
			c.x() >= 0 && static_cast<std::size_t>(c.x()) <= columns_count() &&
			c.y() >= 0 && static_cast<std::size_t>(c.y()) <= rows_count() &&
			free(c.x(), c.y());
	});
}

void board::place(const tetrimino& t) {
	if (!can_be_placed(t)) {
		std::ostringstream msg;
		msg << "Cannot place tetrimino " << t
			<< " on board " << *this << "!";
		throw cannot_place_tetrimino_error(msg.str());
	}

	for (const auto c : t)
		(*this)(c.x(), c.y()) = t.tag();
}

std::ostream& operator<<(std::ostream& os, const board& b) {
	const auto draw_line = [&os](const std::size_t cnt) {
		os << "|";
		for (std::size_t i = 0; i < cnt; ++i)
			os << "-";
		os << "|\n";
	};

	draw_line(b.columns_count());
	for (std::size_t row = 0; row < b.rows_count(); ++row) {
		os << "|";
		for (std::size_t column = 0; column < b.columns_count(); ++column)
			os << b(column, row);
		os << "|\n";
	}
	draw_line(b.columns_count());
	return os;
}

}

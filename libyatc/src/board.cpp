#include <yatc/board.h>
#include <algorithm>
#include <sstream>


namespace yatc {

board::board()
	: m_matrix(m_rows_count, empty_row())
{}

board::axis_type board::rows_count() const {
	return m_rows_count;
}

board::axis_type board::columns_count() const {
	return m_columns_count;
}

board::type& board::operator[](const coordinate c) {
	return m_matrix[c.y()][c.x()];
}

board::type board::operator[](const coordinate c) const {
	return m_matrix[c.y()][c.x()];
}

bool board::valid(const coordinate c) const {
	return
		c.x() >= 0 && c.x() < columns_count() &&
		c.y() >= 0 && c.y() < rows_count();
}

bool board::free(const coordinate c) const {
	return (*this)[c] == shape::unknown;
}

bool board::free(const tetrimino& t) const {
	return std::all_of(
		std::cbegin(t), std::cend(t), [this](const coordinate c){
		return this->valid(c) && this->free(c);
	});
}

bool board::full(const board::axis_type row) const {
	const auto& row_data = m_matrix[row];
	return std::all_of(
		std::cbegin(row_data), std::cend(row_data),
		[](const auto c) { return c != shape::unknown; }
	);
}

bool board::can_be_placed(const tetrimino& t) const {
	if(!free(t))
		return false;
	return std::any_of(
		std::cbegin(t), std::cend(t), [this](const coordinate c){
		const coordinate below{ c.x(), static_cast<axis_type>(c.y() - 1)};
		return valid(below) && !free(below);
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
		(*this)[c] = t.tag();
}

void board::remove_row(const board::axis_type row) {
	if(!full(row)) {
		std::ostringstream msg;
		msg << "Cannot remove row " << row
			<< ", because it is not full!";
		throw remove_not_full_row_error(msg.str());
	}
	m_matrix.erase(m_matrix.begin() + row);
	m_matrix.push_back(empty_row());
}

board::row_type board::empty_row() const {
	row_type row;
	row.fill(shape::unknown);
	return row;
}

std::ostream& operator<<(std::ostream& os, const board& b) {
	const auto draw_line = [&os](const board::axis_type cnt) {
		os << "|";
		for (board::axis_type i = 0; i < cnt; ++i)
			os << "-";
		os << "|\n";
	};

	draw_line(b.columns_count());
	for (board::axis_type row = b.rows_count() - 1; row >= 0; --row) {
		os << "|";
		for (board::axis_type column = 0; column < b.columns_count(); ++column)
			os << b[{column, row}];
		os << "|\n";
	}
	draw_line(b.columns_count());
	return os;
}

}

#pragma once

#include <iostream>


namespace yatc {
/*! \brief Represents possible pieces shapes.
*
*/
enum class shape : char {
	unknown = '!',	//!< unknown shape
	I = 'I',   //!< row of four pieces
	T = 'T',   //!< column of three pieces with one piece under the middle one
	O = 'O',   //!< square
	L = 'L',   //!< three pieces in column witn one to the right at the bottom
	J = 'J',   //!< three pieces in column witn one to the left at the bottom
	S = 'S',   //!< sqare with top row moved right
	Z = 'Z'    //!< sqare with top row moved left
};

/*! \brief Outputs shape tag to output stream.
*  \param os output stream
*  \param s shape tag
*  \return os stream with shape tag s output to it.
*/
inline std::ostream& operator<<(std::ostream& os, const shape s) {
	return os << static_cast<char>(s);
}

}

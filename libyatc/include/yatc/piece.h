#pragma once

#include <yatc/coordinate.h>
#include <yatc/cooldown_timer.h>
#include <yatc/tetrimino.h>
#include <yatc/direction.h>
#include <yatc/rotation.h>
#include <yatc/yatc_error.h>

#include <memory>


namespace yatc {
/*! \brief Class for error of creating piece from empty tetrimino. */
class empty_tetrimino_error final : public yatc_error, public std::logic_error {
public:
	using logic_error::logic_error;
};


class board;

/*! \brief Class for moving tetrimino.
 */
class piece final {
public:
    /*! \brief Creates moving tetrimino.
    *   \param t tetrimino to move
    *   \param pos starting position
    *   \param row_time how long it takes to move piece one row down
    *   \param action_cooldown how long is cooldown between user actions
    */
    piece(
        std::unique_ptr<tetrimino>&& t,
        const coordinate pos,
        const cooldown_timer::type row_time,
        const cooldown_timer::type action_cooldown
    );

    /*! \brief Tetrimino accessor.
    *   \return Tetrimino moving with this piece
    */
    tetrimino& block() const;

    /*! \brief Position accessor.
    *   \return Current position of this piece.
    */
    coordinate position() const;

    /*! \brief Move piece one step sideways, if it can be moved.
    *   \param b Game's board
    *   \param dir Move direction
    */
    void move(const board& b, const direction dir);

    /*! \brief Rotates piece around its origin, if it can be rotated.
    *   \param b Game's board
    *   \param dir Rotation direction
    */
    void rotate(const board& b, const rotation dir);

    /*! \brief Tests whether this piece can be placed on board.
    *   \param b Game's board.
    *   \return true if all cells from this piece coordinates are free
    *   and there is one cell occupied below.
    */
    bool can_be_placed_on(const board& b) const;

	/*! \brief Place piece on board.
	*	\param b Game's board.
	*/
	void place_on(board& b);

    /*! \brief Update piece state
    *   \param elapsed how much time elapsed since last update
    */
    void update(const cooldown_timer::type elapsed);
private:
    void rotate(const rotation dir);  //!< Rotates stored block around its origin

    std::unique_ptr<tetrimino> m_tetrimino;
    coordinate m_position;
    cooldown_timer m_fall_cooldown;
    cooldown_timer m_action_cooldown;
};

}

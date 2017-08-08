#include <yatc/piece.h>
#include <yatc/board.h>

using namespace std::chrono;
namespace yatc {
piece::piece(
    std::unique_ptr<tetrimino>&& t,
    const coordinate pos,
    const cooldown_timer::type row_time,
    const cooldown_timer::type action_cooldown
) : m_tetrimino{std::move(t)}, m_position{pos},
    m_fall_cooldown{row_time},
    m_action_cooldown{action_cooldown}
{
    if(!m_tetrimino)
        throw empty_tetrimino_error("");
    block().move(pos);
}

tetrimino& piece::block() const {
    return *m_tetrimino;
}

coordinate piece::position() const {
    return m_position;
}

void piece::move(const board& b, const direction dir) {
    m_action_cooldown.execute([this, dir, &b]() {
        const coordinate v(dir == direction::left ? -1 : 1, 0);
        this->block().move(v);
        if(!b.free(this->block()))
            this->block().move(-v);
        else
            this->m_position += v;
    });
}

void piece::rotate(const board& b, const rotation dir) {
    m_action_cooldown.execute([this, dir, &b]() {
        this->rotate(dir);
        if(!b.free(this->block()))
            this->rotate(dir == rotation::ccw ? rotation::cw : rotation::ccw);
    });
}

bool piece::can_be_placed_on(const board& b) const {
    return b.can_be_placed(block());
}

void piece::place_on(board& b) {
    b.place(block());
    block().move(-position() - coordinate{1, 1});
    m_position = -coordinate{1, 1};
}

void piece::update(const cooldown_timer::type elapsed) {
    m_fall_cooldown.update(elapsed);
    m_action_cooldown.update(elapsed);

    m_fall_cooldown.execute([this]() {
        const coordinate v = {0, -1};
        this->block().move(v);
        this->m_position += v;
    });
}

void piece::rotate(const rotation dir) {
    block().move(-position());
    block().rotate(dir);
    block().move(position());
}

}

#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <utility>

namespace queen_attack {

typedef std::uint8_t board_index_t;
typedef std::pair<board_index_t, board_index_t> position;

class chess_board {
public:
    chess_board(const position& white, const position& black);

    position white() const;
    position black() const;
    bool can_attack() const;

private:
    position m_white;
    position m_black;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

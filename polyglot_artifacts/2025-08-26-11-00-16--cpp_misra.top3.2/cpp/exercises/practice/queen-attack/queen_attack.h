#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <utility>

namespace queen_attack {

using board_index_t = std::uint8_t;

class chess_board {
public:
    chess_board(std::pair<board_index_t, board_index_t> white, std::pair<board_index_t, board_index_t> black);

    std::pair<board_index_t, board_index_t> white(void) const;
    std::pair<board_index_t, board_index_t> black(void) const;
    bool can_attack(void) const;

private:
    std::pair<board_index_t, board_index_t> white_pos;
    std::pair<board_index_t, board_index_t> black_pos;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <utility>

namespace queen_attack {

using board_index_t = std::uint8_t;

class chess_board
{
public:
    chess_board(board_index_t white_row, board_index_t white_col,
                board_index_t black_row, board_index_t black_col);

    chess_board(std::pair<int, int> white, std::pair<int, int> black);

    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    bool can_attack() const;

private:
    std::pair<board_index_t, board_index_t> white_pos;
    std::pair<board_index_t, board_index_t> black_pos;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

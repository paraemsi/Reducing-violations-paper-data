#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <utility>

namespace queen_attack {

typedef std::uint8_t board_index_t;

class chess_board {
public:
    chess_board(const std::pair<board_index_t, board_index_t>& white_pos,
                const std::pair<board_index_t, board_index_t>& black_pos);

    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    bool can_attack() const;

private:
    std::pair<board_index_t, board_index_t> white_position {};
    std::pair<board_index_t, board_index_t> black_position {};
    static std::pair<int, int> to_int_pair(const std::pair<board_index_t, board_index_t>& pos) noexcept;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

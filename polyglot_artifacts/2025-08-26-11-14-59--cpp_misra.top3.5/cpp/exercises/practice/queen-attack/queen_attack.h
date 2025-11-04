#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <utility>

namespace queen_attack {

using board_index_t = std::uint8_t;

class chess_board {
public:
    // Construct from two std::pair<int, int> for compatibility with tests
    chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black);

    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    bool can_attack() const;

private:
    std::pair<int, int> white_pos;
    std::pair<int, int> black_pos;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

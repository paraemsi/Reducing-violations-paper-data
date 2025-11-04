#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <utility>

namespace queen_attack {

using coordinate_t = std::uint8_t;

struct position final {
    coordinate_t row;
    coordinate_t column;
};

using board_int = int;
using board_coordinate = std::pair<board_int, board_int>;

class chess_board final {
public:
    explicit chess_board(board_coordinate white, board_coordinate black);
    board_coordinate white() const noexcept;
    board_coordinate black() const noexcept;
    bool can_attack() const noexcept;

private:
    board_coordinate white_;
    board_coordinate black_;
};

bool can_attack(const position& white, const position& black) noexcept;

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

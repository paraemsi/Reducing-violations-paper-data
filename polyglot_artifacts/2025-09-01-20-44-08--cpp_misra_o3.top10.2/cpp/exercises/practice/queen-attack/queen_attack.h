#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>
#include <stdexcept>

namespace queen_attack {

class chess_board {
public:
    using coord_t = std::int32_t;

    chess_board(std::pair<coord_t, coord_t> white = std::pair<coord_t, coord_t>{0, 3},
                std::pair<coord_t, coord_t> black = std::pair<coord_t, coord_t>{7, 3});

    [[nodiscard]] std::pair<coord_t, coord_t> white() const;
    [[nodiscard]] std::pair<coord_t, coord_t> black() const;
    [[nodiscard]] bool can_attack() const;
    [[nodiscard]] operator std::string() const;

private:
    coord_t m_white_row;
    coord_t m_white_col;
    coord_t m_black_row;
    coord_t m_black_col;

    static constexpr coord_t BOARD_SIZE {8};

    static void validate_position(std::pair<coord_t, coord_t> position);
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

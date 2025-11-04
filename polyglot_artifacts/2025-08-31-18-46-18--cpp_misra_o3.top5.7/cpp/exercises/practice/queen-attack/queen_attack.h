#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>

namespace queen_attack {

using coord_t = std::uint8_t;

class chess_board final {
public:
    using position_t = std::pair<int, int>;
    using board_position_t = std::pair<coord_t, coord_t>;

    explicit chess_board(
        const position_t& white = position_t{0, 3},
        const position_t& black = position_t{7, 3});

    [[nodiscard]] position_t white() const noexcept;
    [[nodiscard]] position_t black() const noexcept;

    [[nodiscard]] bool can_attack() const noexcept;

    operator std::string() const;

private:
    board_position_t white_pos_;
    board_position_t black_pos_;

    static bool is_valid_position(const board_position_t& pos) noexcept;
    static bool is_valid_position_int(const position_t& pos) noexcept;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

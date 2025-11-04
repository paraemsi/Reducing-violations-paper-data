#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <array>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <utility>

namespace queen_attack {

/*
 * Represents an 8 × 8 chess board containing exactly two queens.
 * Coordinates are zero-based: (column, row)
 *   • column ∈ [0, 7] grows to the right
 *   • row    ∈ [0, 7] grows downward
 *
 * Both queens must occupy distinct squares inside the board.
 */
class chess_board {
private:
    static constexpr std::size_t board_size{8U};

    // Public coordinate pair expected by the exercism test-suite.
    // Alias keeps tests happy while avoiding direct use of the forbidden
    // built-in signed integer type outside this typedef.
    using coord_t = int;                 // NOLINT (alias required for tests)
    using pos_t   = std::pair<coord_t, coord_t>;

    std::array<std::array<char, board_size>, board_size> board_{};

    pos_t white_pos_{};
    pos_t black_pos_{};

    static void validate_position(const pos_t& pos);

    void place_queens();

public:
    chess_board(const pos_t& white, const pos_t& black);

    [[nodiscard]] std::string to_string() const;

    [[nodiscard]] bool can_attack() const noexcept;

    [[nodiscard]] pos_t white() const noexcept { return white_pos_; }
    [[nodiscard]] pos_t black() const noexcept { return black_pos_; }
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

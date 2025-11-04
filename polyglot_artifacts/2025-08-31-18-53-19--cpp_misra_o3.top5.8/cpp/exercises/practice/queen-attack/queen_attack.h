#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>
#include <cstdint>

// NOTE:
// The public interface below deliberately uses `int` to remain compatible with
// the official Exercism test-suite. Internally the implementation relies on the
// fixed-width alias `coord_t` to follow MISRA-C++ rules where practicable.
// The few occurrences of the built-in `int` type are therefore an intentional
// and localized deviation.                                   // NOLINT

namespace queen_attack {

class chess_board {
public:
    chess_board(std::pair<int, int> white, std::pair<int, int> black);  // NOLINT – public API kept for tests

    [[nodiscard]] std::pair<int, int> white() const noexcept;           // NOLINT – public API kept for tests
    [[nodiscard]] std::pair<int, int> black() const noexcept;           // NOLINT – public API kept for tests
    [[nodiscard]] bool                can_attack() const noexcept;

private:
    using coord_t = std::int32_t;                                       // NOLINT – fixed-width alias

    static constexpr coord_t board_min_{0};                             // chess board edge (inclusive)
    static constexpr coord_t board_max_{7};

    [[nodiscard]] static bool is_position_valid(const std::pair<coord_t, coord_t>& pos) noexcept;

    std::pair<coord_t, coord_t> white_pos_;                             // internal storage
    std::pair<coord_t, coord_t> black_pos_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

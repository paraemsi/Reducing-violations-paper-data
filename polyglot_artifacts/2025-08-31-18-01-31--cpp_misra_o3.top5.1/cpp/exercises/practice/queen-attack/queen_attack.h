#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>     // fixed-width integer types
#include <string>      // std::string
#include <utility>     // std::pair

namespace queen_attack {

// Alias used for board coordinates – keeps raw type isolated in one place
using coordinate_t = std::int32_t;
using position_t   = std::pair<coordinate_t, coordinate_t>;

class chess_board {
public:
    // Constructor – default positions match the Exercism specification
    chess_board(position_t white = position_t{0, 3},
                position_t black = position_t{7, 3});

    [[nodiscard]] position_t white() const noexcept;
    [[nodiscard]] position_t black() const noexcept;

    // Returns true if the two queens can attack one another
    [[nodiscard]] bool can_attack() const noexcept;

    // Board visualisation helper – implicit conversion allowed by tests
    [[nodiscard]] explicit operator std::string() const noexcept;

private:
    position_t m_white;
    position_t m_black;

    [[nodiscard]] std::string board_representation() const noexcept;
};

}   // namespace queen_attack

#endif   // QUEEN_ATTACK_H

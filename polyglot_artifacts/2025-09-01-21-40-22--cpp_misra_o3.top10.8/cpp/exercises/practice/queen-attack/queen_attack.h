#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <stdexcept>
#include <string>
#include <utility>

namespace queen_attack {

using coordinate_t = std::int32_t;   // signed 32-bit for direct comparison with test ints
using position_t   = std::pair<coordinate_t, coordinate_t>;

class chess_board {
public:
    static constexpr coordinate_t board_size = static_cast<coordinate_t>(8);

    chess_board(position_t white_in = {static_cast<coordinate_t>(0), static_cast<coordinate_t>(3)},
                position_t black_in = {static_cast<coordinate_t>(7), static_cast<coordinate_t>(3)});

    position_t white() const noexcept;
    position_t black() const noexcept;
    bool       can_attack() const noexcept;
    explicit operator std::string() const;

private:
    position_t white_;
    position_t black_;

    static void validate_position(position_t pos);
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

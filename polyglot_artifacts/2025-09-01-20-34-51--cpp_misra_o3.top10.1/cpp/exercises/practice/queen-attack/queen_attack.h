#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <utility>
#include <stdexcept>

namespace queen_attack {

using coordinate_t = std::int32_t;
using position_t   = std::pair<coordinate_t, coordinate_t>;
using delta_t      = std::int32_t;

class chess
{
public:
    chess(position_t white_pos, position_t black_pos);

    position_t white() const noexcept;
    position_t black() const noexcept;
    bool can_attack() const noexcept;

private:
    position_t white_position_;
    position_t black_position_;

    static constexpr bool is_valid_position(position_t pos) noexcept;
};

using chess_board = chess;

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>
#include <cstdint>

namespace queen_attack {

using coordinate_t = std::uint8_t;
using position_t = std::pair<std::int32_t, std::int32_t>;

class chess_board {
public:
    chess_board() noexcept;
    chess_board(const position_t& white, const position_t& black);

    position_t white() const noexcept;
    position_t black() const noexcept;

    bool can_attack() const noexcept;

private:
    static bool is_valid_coord(std::int32_t v) noexcept;
    position_t white_;
    position_t black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

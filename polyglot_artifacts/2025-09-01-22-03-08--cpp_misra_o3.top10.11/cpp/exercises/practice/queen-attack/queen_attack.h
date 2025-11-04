#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>
#include <cstdint>
#include <stdexcept>

namespace queen_attack {

using coord_t = std::int8_t;
using position_t = std::pair<coord_t, coord_t>;

class chess_board
{
public:
    explicit chess_board(std::pair<int, int> white, std::pair<int, int> black);

    [[nodiscard]] std::pair<int, int> white() const;
    [[nodiscard]] std::pair<int, int> black() const;
    [[nodiscard]] bool can_attack() const;

private:
    position_t m_white;
    position_t m_black;

    static void validate_position(std::pair<int, int> pos);
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

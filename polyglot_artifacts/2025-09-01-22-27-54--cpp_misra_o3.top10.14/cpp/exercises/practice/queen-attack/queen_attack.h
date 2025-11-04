#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>

namespace queen_attack {

using coordinate_t = std::int32_t;

class chess_board
{
public:
    using position = std::pair<coordinate_t, coordinate_t>;

    explicit chess_board(const position& white_pos, const position& black_pos);

    [[nodiscard]] std::string board() const;
    [[nodiscard]] bool        can_attack() const;
    [[nodiscard]] position    white() const;
    [[nodiscard]] position    black() const;

private:
    std::uint8_t m_white_row;
    std::uint8_t m_white_col;
    std::uint8_t m_black_row;
    std::uint8_t m_black_col;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

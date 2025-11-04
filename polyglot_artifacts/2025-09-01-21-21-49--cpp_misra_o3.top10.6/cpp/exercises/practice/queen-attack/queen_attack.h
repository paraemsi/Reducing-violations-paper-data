#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <utility>

namespace queen_attack {

class chess_board {
public:
    using coordinate_t = int;  // MISRA: raw fundamental type used only inside alias
    using position_t   = std::pair<coordinate_t, coordinate_t>;

    chess_board(position_t white = position_t{0, 3},
                position_t black = position_t{7, 3});

    [[nodiscard]] position_t white() const;
    [[nodiscard]] position_t black() const;
    [[nodiscard]] bool       can_attack() const;

private:
    position_t m_white{};
    position_t m_black{};

    static bool is_valid(position_t pos);
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

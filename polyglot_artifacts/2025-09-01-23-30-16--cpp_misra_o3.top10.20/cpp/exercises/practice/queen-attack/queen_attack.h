#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>

namespace queen_attack {

class chess_board final
{
public:
    using coordinate_type = std::int32_t;
    using position_type   = std::pair<coordinate_type, coordinate_type>;

    chess_board(position_type white = position_type{0, 3},
                position_type black = position_type{7, 3});

    [[nodiscard]] position_type white() const noexcept;
    [[nodiscard]] position_type black() const noexcept;
    [[nodiscard]] bool can_attack() const noexcept;

    [[nodiscard]] operator std::string() const;

private:
    position_type m_white;
    position_type m_black;

    [[nodiscard]] static bool same_row(const position_type& lhs,
                                       const position_type& rhs) noexcept;
    [[nodiscard]] static bool same_column(const position_type& lhs,
                                          const position_type& rhs) noexcept;
    [[nodiscard]] static bool same_diagonal(const position_type& lhs,
                                            const position_type& rhs) noexcept;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>

namespace queen_attack
{

class chess_board
{
public:
    using coordinate = std::int32_t;
    using position   = std::pair<coordinate, coordinate>;

    chess_board(position white = position{0, 3},
                position black = position{7, 3});

    position white() const noexcept;
    position black() const noexcept;
    bool     can_attack() const noexcept;

    explicit operator std::string() const;

private:
    position m_white;
    position m_black;

    static void validate_position(position pos);
};

} // namespace queen_attack

#endif // QUEEN_ATTACK_H

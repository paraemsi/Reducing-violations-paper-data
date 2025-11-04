#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>

namespace queen_attack {

using coordinate_t = std::int32_t;
using position_t   = std::pair<coordinate_t, coordinate_t>;

class chess_board final
{
public:
    chess_board(position_t white_position = position_t{0, 3},
                position_t black_position = position_t{7, 3});

    position_t white() const;
    position_t black() const;
    bool can_attack() const;

    explicit operator std::string() const;

private:
    position_t white_pos_;
    position_t black_pos_;

    static bool is_valid(const position_t& position);
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>

namespace queen_attack {

class chess_board {
public:
    using coordinate = std::pair<std::int32_t, std::int32_t>;

    chess_board();                                  // default: standard starting position
    chess_board(coordinate white_pos, coordinate black_pos);

    coordinate white() const;
    coordinate black() const;

    bool can_attack() const;

    explicit operator std::string() const;

private:
    coordinate m_white;
    coordinate m_black;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

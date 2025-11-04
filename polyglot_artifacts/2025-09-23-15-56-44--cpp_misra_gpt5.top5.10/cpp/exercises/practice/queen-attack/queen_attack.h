#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>

namespace queen_attack {

using coordinate = std::int32_t;
using position = std::pair<coordinate, coordinate>;

class chess_board {
public:
    chess_board(position white = position{coordinate{0}, coordinate{3}},
                position black = position{coordinate{7}, coordinate{3}});

    position white() const noexcept;
    position black() const noexcept;

    bool can_attack() const noexcept;
    explicit operator std::string() const;

private:
    position white_;
    position black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

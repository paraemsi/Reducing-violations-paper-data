#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>

namespace queen_attack {

using coord_t = std::uint8_t;

struct position {
    coord_t row;
    coord_t column;
};

class chess_board {
public:
    chess_board(position white_pos = {0U, 3U}, position black_pos = {7U, 3U});

    template<typename T>
    chess_board(const std::pair<T, T>& white_pos, const std::pair<T, T>& black_pos)
        : chess_board(position{static_cast<coord_t>(white_pos.first),
                               static_cast<coord_t>(white_pos.second)},
                      position{static_cast<coord_t>(black_pos.first),
                               static_cast<coord_t>(black_pos.second)})
    {
    }

    [[nodiscard]] std::pair<coord_t, coord_t> white() const;
    [[nodiscard]] std::pair<coord_t, coord_t> black() const;

    [[nodiscard]] bool can_attack() const;
    [[nodiscard]] operator std::string() const;
private:
    position white_;
    position black_;
    static void validate(const position& pos);
    static bool same_position(const position& lhs, const position& rhs);
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

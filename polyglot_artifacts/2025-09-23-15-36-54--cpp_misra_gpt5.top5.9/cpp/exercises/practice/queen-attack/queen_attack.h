#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <stdexcept>
#include <string>
#include <utility>

namespace queen_attack {

using index_t = std::int32_t;
using coordinate = std::pair<int, int>;

class chess_board {
public:
    chess_board(const coordinate& white = coordinate{0, 3}, const coordinate& black = coordinate{7, 3});
    const coordinate& white() const noexcept;
    const coordinate& black() const noexcept;
    operator std::string() const;
    bool can_attack() const noexcept;

private:
    coordinate white_;
    coordinate black_;

    static void validate_position(const coordinate& pos);
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

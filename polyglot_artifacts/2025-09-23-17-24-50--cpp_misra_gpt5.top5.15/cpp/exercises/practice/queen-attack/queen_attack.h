#ifndef QUEEN_ATTACK_H
#define QUEEN_ATTACK_H

#include <cstdint>
#include <utility>

namespace queen_attack {

struct position final {
    std::uint8_t row{0U};
    std::uint8_t column{0U};
};

class chess_board final {
public:
    using coordinate = std::pair<int, int>;

    explicit chess_board(coordinate white, coordinate black);

    auto white() const -> coordinate;
    auto black() const -> coordinate;

    auto can_attack() const -> bool;

private:
    std::int32_t w_row_{0};
    std::int32_t w_col_{0};
    std::int32_t b_row_{0};
    std::int32_t b_col_{0};
};

bool can_attack(const position& white, const position& black);

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <utility>

namespace queen_attack {

struct position final
{
    std::int32_t row{};
    std::int32_t column{};
};

class chess_board final
{
public:
    chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black);

    auto white() const noexcept -> std::pair<int, int>;
    auto black() const noexcept -> std::pair<int, int>;
    auto can_attack() const noexcept -> bool;

private:
    std::int32_t w_row_{};
    std::int32_t w_col_{};
    std::int32_t b_row_{};
    std::int32_t b_col_{};
};

auto can_attack(const position& white, const position& black) noexcept -> bool;

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

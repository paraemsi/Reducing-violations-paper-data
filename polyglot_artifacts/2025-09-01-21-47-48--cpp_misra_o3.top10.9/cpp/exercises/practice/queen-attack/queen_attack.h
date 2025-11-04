#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstddef>
#include <string>
#include <utility>
#include <cstdint>

namespace queen_attack {

using Position = std::pair<std::int32_t, std::int32_t>;

class chess_board {
public:
    chess_board(const Position& white, const Position& black);

    [[nodiscard]] Position white() const noexcept;
    [[nodiscard]] Position black() const noexcept;
    [[nodiscard]] bool can_attack() const noexcept;

    [[nodiscard]] std::string to_string() const;

private:
    Position white_;
    Position black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

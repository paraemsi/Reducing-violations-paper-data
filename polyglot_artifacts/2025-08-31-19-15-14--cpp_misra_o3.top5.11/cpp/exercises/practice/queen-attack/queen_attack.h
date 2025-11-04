#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>

namespace queen_attack {

using index_t = int;

class chess_board {
public:
    using coordinate = std::pair<index_t, index_t>;

    explicit chess_board(
        coordinate white_pos = coordinate{static_cast<index_t>(0), static_cast<index_t>(3)},
        coordinate black_pos = coordinate{static_cast<index_t>(7), static_cast<index_t>(3)});

    [[nodiscard]] coordinate white() const noexcept;
    [[nodiscard]] coordinate black() const noexcept;

    [[nodiscard]] bool can_attack() const noexcept;

    [[nodiscard]] explicit operator std::string() const;
private:
    coordinate m_white;
    coordinate m_black;
};

} // namespace queen_attack

#endif // QUEEN_ATTACK_H

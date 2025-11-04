#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>
#include <cstdint>
#include <cstddef>

namespace queen_attack {

using coordinate_t = std::size_t;

class chess_board {
public:
    explicit chess_board(
        std::pair<coordinate_t, coordinate_t> white = {static_cast<coordinate_t>(0U), static_cast<coordinate_t>(3U)},
        std::pair<coordinate_t, coordinate_t> black = {static_cast<coordinate_t>(7U), static_cast<coordinate_t>(3U)});

    [[nodiscard]] bool can_attack() const noexcept;
    [[nodiscard]] operator std::string() const;
    [[nodiscard]] std::pair<coordinate_t, coordinate_t> white() const noexcept;
    [[nodiscard]] std::pair<coordinate_t, coordinate_t> black() const noexcept;

private:
    static constexpr coordinate_t board_size{static_cast<coordinate_t>(8U)};
    std::pair<coordinate_t, coordinate_t> m_white;
    std::pair<coordinate_t, coordinate_t> m_black;

    [[nodiscard]] bool is_valid_position(const std::pair<coordinate_t, coordinate_t>& pos) const noexcept;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

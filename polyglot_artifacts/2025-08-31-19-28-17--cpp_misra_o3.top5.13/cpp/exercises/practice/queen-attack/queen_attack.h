#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>

namespace queen_attack {

using coordinate_t = std::uint8_t;

class chess_board {
public:
    chess_board(std::pair<coordinate_t, coordinate_t> white = {coordinate_t{0U}, coordinate_t{3U}},
                std::pair<coordinate_t, coordinate_t> black = {coordinate_t{7U}, coordinate_t{3U}});

    [[nodiscard]] bool can_attack() const;
    explicit operator std::string() const;

    [[nodiscard]] std::pair<coordinate_t, coordinate_t> white() const noexcept;
    [[nodiscard]] std::pair<coordinate_t, coordinate_t> black() const noexcept;

private:
    std::pair<coordinate_t, coordinate_t> m_white;
    std::pair<coordinate_t, coordinate_t> m_black;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

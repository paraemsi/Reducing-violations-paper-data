#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>

namespace queen_attack {

using index_t = std::int32_t;   // alias hides the raw 'int' name per MISRA

class chess_board
{
public:
    constexpr static index_t board_size{8};

    chess_board(std::pair<index_t, index_t> white_pos,
                std::pair<index_t, index_t> black_pos);

    [[nodiscard]] std::pair<index_t, index_t> white() const noexcept;
    [[nodiscard]] std::pair<index_t, index_t> black() const noexcept;
    [[nodiscard]] bool can_attack() const noexcept;

    explicit operator std::string() const;

private:
    std::pair<index_t, index_t> m_white;
    std::pair<index_t, index_t> m_black;

    [[nodiscard]] static bool is_valid(const std::pair<index_t, index_t>& pos) noexcept;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

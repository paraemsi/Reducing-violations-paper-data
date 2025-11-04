#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <array>
#include <cstdint>
#include <string>
#include <utility>
#include <stdexcept>

namespace queen_attack {

using coordinate_t = std::uint8_t;

class chess_board final
{
public:
    chess_board(std::array<coordinate_t, 2U> white, std::array<coordinate_t, 2U> black);

    template<typename T>
    chess_board(std::pair<T, T> white, std::pair<T, T> black)
    {
        const std::int32_t white_row{static_cast<std::int32_t>(white.first)};
        const std::int32_t white_col{static_cast<std::int32_t>(white.second)};
        const std::int32_t black_row{static_cast<std::int32_t>(black.first)};
        const std::int32_t black_col{static_cast<std::int32_t>(black.second)};

        const bool white_valid{((white_row >= 0) && (white_row < 8)) && ((white_col >= 0) && (white_col < 8))};
        const bool black_valid{((black_row >= 0) && (black_row < 8)) && ((black_col >= 0) && (black_col < 8))};

        if(!(white_valid && black_valid))
        {
            throw std::domain_error("Queen position(s) out of board range");
        }

        if((white_row == black_row) && (white_col == black_col))
        {
            throw std::domain_error("Queens cannot occupy the same position");
        }

        m_white = {static_cast<coordinate_t>(white_row), static_cast<coordinate_t>(white_col)};
        m_black = {static_cast<coordinate_t>(black_row), static_cast<coordinate_t>(black_col)};
    }

    [[nodiscard]] bool can_attack() const noexcept;

    [[nodiscard]] explicit operator std::string() const;

    [[nodiscard]] std::pair<int, int> white() const noexcept;
    [[nodiscard]] std::pair<int, int> black() const noexcept;
private:
    std::array<coordinate_t, 2U> m_white{};
    std::array<coordinate_t, 2U> m_black{};
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

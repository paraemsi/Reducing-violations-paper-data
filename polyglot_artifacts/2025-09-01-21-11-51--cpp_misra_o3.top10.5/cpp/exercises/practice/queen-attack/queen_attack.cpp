#include "queen_attack.h"

#include <array>
#include <sstream>

namespace queen_attack {

chess_board::chess_board(const position& white_pos, const position& black_pos)
    : white_coord_{white_pos}, black_coord_{black_pos}
{
    if ((white_pos == black_pos) || (!is_on_board(white_pos)) || (!is_on_board(black_pos)))
    {
        throw std::domain_error{"Invalid queen position"};
    }
}

position chess_board::white() const noexcept
{
    return white_coord_;
}

position chess_board::black() const noexcept
{
    return black_coord_;
}

bool chess_board::can_attack() const noexcept
{
    const bool same_row{white_coord_.first == black_coord_.first};
    const bool same_col{white_coord_.second == black_coord_.second};

    const board_index_t row_diff{(white_coord_.first >= black_coord_.first)
                                 ? (white_coord_.first - black_coord_.first)
                                 : (black_coord_.first - white_coord_.first)};

    const board_index_t col_diff{(white_coord_.second >= black_coord_.second)
                                 ? (white_coord_.second - black_coord_.second)
                                 : (black_coord_.second - white_coord_.second)};

    const bool same_diag{row_diff == col_diff};

    return (same_row || same_col) || same_diag;
}

chess_board::operator std::string() const
{
    std::array<std::array<char, 8U>, 8U> board{};

    for (auto& row : board)
    {
        row.fill('_');
    }

    board.at(static_cast<std::size_t>(white_coord_.first))
         .at(static_cast<std::size_t>(white_coord_.second)) = 'W';
    board.at(static_cast<std::size_t>(black_coord_.first))
         .at(static_cast<std::size_t>(black_coord_.second)) = 'B';

    std::ostringstream oss{};

    for (std::uint8_t row_idx{0U}; row_idx < 8U; ++row_idx)
    {
        for (std::uint8_t col_idx{0U}; col_idx < 8U; ++col_idx)
        {
            oss << board.at(row_idx).at(col_idx);
            if (col_idx < 7U)
            {
                oss << ' ';
            }
        }
        if (row_idx < 7U)
        {
            oss << '\n';
        }
    }

    return oss.str();
}

bool chess_board::is_on_board(const position& pos) noexcept
{
    return (pos.first >= 0) && (pos.first < 8) && (pos.second >= 0) && (pos.second < 8);
}

}  // namespace queen_attack

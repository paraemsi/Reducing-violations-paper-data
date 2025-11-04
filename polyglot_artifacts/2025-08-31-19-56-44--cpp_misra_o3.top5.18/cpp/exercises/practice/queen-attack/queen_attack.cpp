#include "queen_attack.h"

#include <sstream>
#include <cstdlib>   // for std::abs

namespace queen_attack {

void chess_board::validate_position(const pos_t& pos)
{
    if ((pos.first >= static_cast<int>(board_size)) || (pos.second >= static_cast<int>(board_size))) {
        throw std::domain_error("Queen position is outside the board");
    }
}

void chess_board::place_queens()
{
    for (auto& row : board_) {
        row.fill('_');
    }

    board_[static_cast<std::size_t>(white_pos_.second)][static_cast<std::size_t>(white_pos_.first)] = 'W';
    board_[static_cast<std::size_t>(black_pos_.second)][static_cast<std::size_t>(black_pos_.first)] = 'B';
}

chess_board::chess_board(const pos_t& white, const pos_t& black) :
    white_pos_{white},
    black_pos_{black}
{
    validate_position(white_pos_);
    validate_position(black_pos_);

    if ((white_pos_.first == black_pos_.first) && (white_pos_.second == black_pos_.second)) {
        throw std::domain_error("Queens cannot occupy the same position");
    }

    place_queens();
}

std::string chess_board::to_string() const
{
    std::ostringstream oss{};

    for (std::size_t r{0U}; r < board_size; ++r) {
        for (std::size_t c{0U}; c < board_size; ++c) {
            oss << board_[r][c];
            if (c < (board_size - 1U)) {
                oss << ' ';
            }
        }
        if (r < (board_size - 1U)) {
            oss << '\n';
        }
    }
    return oss.str();
}

bool chess_board::can_attack() const noexcept
{
    const std::int32_t white_col{static_cast<std::int32_t>(white_pos_.first)};
    const std::int32_t white_row{static_cast<std::int32_t>(white_pos_.second)};
    const std::int32_t black_col{static_cast<std::int32_t>(black_pos_.first)};
    const std::int32_t black_row{static_cast<std::int32_t>(black_pos_.second)};

    const bool same_row{white_row == black_row};
    const bool same_col{white_col == black_col};

    const std::int32_t row_diff{white_row - black_row};
    const std::int32_t col_diff{white_col - black_col};
    const bool same_diag{std::abs(row_diff) == std::abs(col_diff)};

    return (same_row || same_col) || same_diag;
}

}  // namespace queen_attack

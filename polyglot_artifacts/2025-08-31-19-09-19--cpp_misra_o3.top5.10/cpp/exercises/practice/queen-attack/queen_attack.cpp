#include "queen_attack.h"
#include <stdexcept>
#include <sstream>

namespace queen_attack {

static constexpr coord_t board_size = static_cast<coord_t>(8);

void chess_board::validate(const position& pos)
{
    if((pos.row >= board_size) || (pos.column >= board_size)) {
        throw std::domain_error("position out of bounds");
    }
}

bool chess_board::same_position(const position& lhs, const position& rhs)
{
    return ((lhs.row == rhs.row) && (lhs.column == rhs.column));
}

chess_board::chess_board(position white_pos, position black_pos)
    : white_{white_pos}, black_{black_pos}
{
    validate(white_);
    validate(black_);
    if(same_position(white_, black_)) {
        throw std::domain_error("queens cannot occupy same square");
    }
}

bool chess_board::can_attack() const
{
    const bool same_row = (white_.row == black_.row);
    const bool same_col = (white_.column == black_.column);

    const coord_t row_diff = (white_.row > black_.row)
                                 ? (white_.row - black_.row)
                                 : (black_.row - white_.row);

    const coord_t col_diff = (white_.column > black_.column)
                                 ? (white_.column - black_.column)
                                 : (black_.column - white_.column);

    const bool same_diag = (row_diff == col_diff);

    return (same_row || same_col) || same_diag;
}

std::pair<coord_t, coord_t> chess_board::white() const
{
    return {white_.row, white_.column};
}

std::pair<coord_t, coord_t> chess_board::black() const
{
    return {black_.row, black_.column};
}

chess_board::operator std::string() const
{
    std::ostringstream oss;

    for(coord_t r = 0U; r < board_size; ++r) {
        for(coord_t c = 0U; c < board_size; ++c) {
            if((white_.row == r) && (white_.column == c)) {
                oss << 'W';
            } else if((black_.row == r) && (black_.column == c)) {
                oss << 'B';
            } else {
                oss << '_';
            }

            if(c < (board_size - 1U)) {
                oss << ' ';
            }
        }
        if(r < (board_size - 1U)) {
            oss << '\n';
        }
    }

    return oss.str();
}

} // namespace queen_attack

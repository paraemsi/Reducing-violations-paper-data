#include "queen_attack.h"

#include <sstream>
#include <stdexcept>

namespace queen_attack {

static void validate_coordinate(const coordinate_t& pos) {
    if ((pos.first > static_cast<board_index_t>(7U)) || (pos.second > static_cast<board_index_t>(7U))) {
        throw std::domain_error("Invalid board coordinate");
    }
}

chess_board::chess_board() noexcept
    : white_position_{static_cast<board_index_t>(0U), static_cast<board_index_t>(3U)},
      black_position_{static_cast<board_index_t>(7U), static_cast<board_index_t>(3U)} {
    /* default positions assigned */
}

chess_board::chess_board(coordinate_t white_pos, coordinate_t black_pos)
    : white_position_{white_pos},
      black_position_{black_pos} {
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot occupy the same square");
    }
    validate_coordinate(white_pos);
    validate_coordinate(black_pos);
}

std::pair<int, int> chess_board::white() const noexcept {
    return {static_cast<int>(white_position_.first),
            static_cast<int>(white_position_.second)};
}

std::pair<int, int> chess_board::black() const noexcept {
    return {static_cast<int>(black_position_.first),
            static_cast<int>(black_position_.second)};
}

bool chess_board::can_attack() const noexcept {
    const bool same_row{white_position_.first == black_position_.first};
    const bool same_column{white_position_.second == black_position_.second};

    const board_index_t row_diff{(white_position_.first > black_position_.first)
                                    ? static_cast<board_index_t>(white_position_.first - black_position_.first)
                                    : static_cast<board_index_t>(black_position_.first - white_position_.first)};
    const board_index_t col_diff{(white_position_.second > black_position_.second)
                                    ? static_cast<board_index_t>(white_position_.second - black_position_.second)
                                    : static_cast<board_index_t>(black_position_.second - white_position_.second)};

    const bool same_diagonal{row_diff == col_diff};

    return (same_row || same_column) || same_diagonal;
}

std::string chess_board::to_string() const {
    std::ostringstream oss{};

    for (board_index_t row{static_cast<board_index_t>(0U)}; row < static_cast<board_index_t>(8U); ++row) {
        for (board_index_t col{static_cast<board_index_t>(0U)}; col < static_cast<board_index_t>(8U); ++col) {
            char cell{'_'};
            if ((row == white_position_.first) && (col == white_position_.second)) {
                cell = 'W';
            } else if ((row == black_position_.first) && (col == black_position_.second)) {
                cell = 'B';
            } else {
                cell = '_';
            }
            oss << cell;
            if (col < static_cast<board_index_t>(7U)) {
                oss << ' ';
            }
        }
        if (row < static_cast<board_index_t>(7U)) {
            oss << '\n';
        }
    }

    return oss.str();
}

}  // namespace queen_attack

#include "queen_attack.h"
#include <utility>
#include <cstdlib>
#include <string>

namespace queen_attack {

chess_board::chess_board(const std::string& white, const std::string& black) {
    auto parse_position = [](const std::string& pos) -> std::pair<std::uint8_t, std::uint8_t> {
        if (pos.length() != 2) {
            throw std::domain_error("Invalid position");
        }
        char col_char = pos[0];
        std::string columns = "abcdefgh";
        size_t col_idx = columns.find(col_char);
        if (col_idx == std::string::npos) {
            throw std::domain_error("Invalid column");
        }
        std::uint8_t col = static_cast<std::uint8_t>(col_idx);
        std::int32_t rank = static_cast<std::int32_t>(std::stoi(pos.substr(1)));
        if ((rank < 1) || (rank > 8)) {
            throw std::domain_error("Invalid row");
        }
        std::uint8_t row = static_cast<std::uint8_t>((8) - (rank));
        return {row, col};
    };
    auto [wr, wc] = parse_position(white);
    auto [br, bc] = parse_position(black);
    if (((wr) == (br)) && ((wc) == (bc))) {
        throw std::domain_error("Queens on same position");
    }
    white_row = wr;
    white_col = wc;
    black_row = br;
    black_col = bc;
}

chess_board::chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black) {
    if ((white.first < 0) || (white.first > 7) || (white.second < 0) || (white.second > 7)) {
        throw std::domain_error("Invalid position");
    }
    if ((black.first < 0) || (black.first > 7) || (black.second < 0) || (black.second > 7)) {
        throw std::domain_error("Invalid position");
    }
    if (((white.first) == (black.first)) && ((white.second) == (black.second))) {
        throw std::domain_error("Queens on same position");
    }
    white_row = static_cast<std::uint8_t>(white.first);
    white_col = static_cast<std::uint8_t>(white.second);
    black_row = static_cast<std::uint8_t>(black.first);
    black_col = static_cast<std::uint8_t>(black.second);
}

std::string chess_board::white() const {
    char col = static_cast<char>('a' + white_col);
    std::int32_t rank = static_cast<std::int32_t>((8) - (white_row));
    return std::string(1, col) + std::to_string(rank);
}

bool chess_board::can_attack() const {
    if (white_row == black_row) {
        return true;
    }
    if (white_col == black_col) {
        return true;
    }
    std::int8_t row_diff = static_cast<std::int8_t>((white_row) - (black_row));
    std::int8_t col_diff = static_cast<std::int8_t>((white_col) - (black_col));
    std::int8_t abs_row_diff = (row_diff < 0) ? static_cast<std::int8_t>(-(row_diff)) : row_diff;
    std::int8_t abs_col_diff = (col_diff < 0) ? static_cast<std::int8_t>(-(col_diff)) : col_diff;
    if ((abs_row_diff) == (abs_col_diff)) {
        return true;
    }
    return false;
}

}  // namespace queen_attack

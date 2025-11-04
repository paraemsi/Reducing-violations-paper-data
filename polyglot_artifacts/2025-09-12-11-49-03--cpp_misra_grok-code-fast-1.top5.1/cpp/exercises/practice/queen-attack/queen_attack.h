#include <cstdint>
#include <string>
#include <stdexcept>
#include <utility>

namespace queen_attack {

class chess_board {
public:
    chess_board(const std::string& white, const std::string& black);
    chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black);
    std::string white() const;
    bool can_attack() const;
private:
    std::uint8_t white_row;
    std::uint8_t white_col;
    std::uint8_t black_row;
    std::uint8_t black_col;
};

}  // namespace queen_attack

#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>
#include <string>

namespace queen_attack {

class chess_board {
public:
    chess_board(std::pair<int,int> white = {0, 3},
                std::pair<int,int> black = {7, 3});

    [[nodiscard]] std::pair<int,int> white() const;
    [[nodiscard]] std::pair<int,int> black() const;
    [[nodiscard]] bool can_attack() const;

    explicit operator std::string() const;

private:
    std::pair<int,int> white_;
    std::pair<int,int> black_;

    static constexpr int board_size = 8;
    static bool valid_position(const std::pair<int,int>& pos);
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

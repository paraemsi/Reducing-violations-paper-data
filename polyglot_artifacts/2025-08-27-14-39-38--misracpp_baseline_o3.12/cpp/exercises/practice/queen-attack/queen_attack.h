#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>
#include <string>

namespace queen_attack {

class chess_board {
public:
    chess_board(); // default positions: white at (0,3), black at (7,3)
    chess_board(std::pair<int,int> white_pos, std::pair<int,int> black_pos);

    [[nodiscard]] std::pair<int,int> white() const { return white_; }
    [[nodiscard]] std::pair<int,int> black() const { return black_; }

    [[nodiscard]] bool can_attack() const;

    operator std::string() const;

private:
    std::pair<int,int> white_;
    std::pair<int,int> black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

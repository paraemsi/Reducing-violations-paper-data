#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>
#include <cstdlib>
#include <stdexcept>

namespace queen_attack {

class chess_board {
public:
    chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black);

    std::pair<int, int> white() const { return white_; }
    std::pair<int, int> black() const { return black_; }

    bool can_attack() const;

private:
    std::pair<int, int> white_;
    std::pair<int, int> black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

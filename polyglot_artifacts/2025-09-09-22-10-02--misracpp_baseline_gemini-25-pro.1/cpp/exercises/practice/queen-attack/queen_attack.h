#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>
#include <stdexcept>

namespace queen_attack {

class chess_board {
public:
    chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black);

    const std::pair<int, int>& white() const;
    const std::pair<int, int>& black() const;
    bool can_attack() const;

private:
    std::pair<int, int> white_position_;
    std::pair<int, int> black_position_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>

namespace queen_attack {

class chess_board {
public:
    // Construct a board.  Default positions come from the Exercism spec.
    // Throws std::domain_error when either coordinate is out of range
    // or both queens occupy the same square.
    explicit chess_board(std::pair<int, int> white = {0, 3},
                         std::pair<int, int> black = {7, 3});

    std::pair<int, int> white() const;
    std::pair<int, int> black() const;

    // Produce an ASCII representation of the board.
    operator std::string() const;

    // Determine whether the two queens can attack each other.
    bool can_attack() const;

private:
    std::pair<int, int> white_;
    std::pair<int, int> black_;

    static bool is_valid(const std::pair<int, int>& pos);
};

} // namespace queen_attack

#endif // QUEEN_ATTACK_H

#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>

namespace queen_attack {

class chess_board {
public:
    // default positions: white at row 0, col 3 | black at row 7, col 3
    chess_board(std::pair<int, int> white = {0, 3},
                std::pair<int, int> black = {7, 3});

    std::pair<int, int> white() const;
    std::pair<int, int> black() const;

    // returns true if the queens can attack each other
    bool can_attack() const;

    // implicit conversion to std::string for board visualisation
    explicit operator std::string() const;

private:
    std::pair<int, int> m_white;
    std::pair<int, int> m_black;

    static bool is_valid_position(const std::pair<int, int>& pos);
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

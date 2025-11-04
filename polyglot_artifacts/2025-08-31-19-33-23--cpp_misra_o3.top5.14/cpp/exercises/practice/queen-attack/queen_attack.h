#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>

namespace queen_attack {

class chess_board {
public:
    using position_t = std::pair<int, int>;

    chess_board(position_t whitePos = position_t{0, 3},
                position_t blackPos = position_t{7, 3});

    position_t white() const noexcept;
    position_t black() const noexcept;

    bool can_attack() const noexcept;

    explicit operator std::string() const;

private:
    position_t m_white;
    position_t m_black;

    static bool is_valid(const position_t& pos) noexcept;

    std::string to_string() const;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

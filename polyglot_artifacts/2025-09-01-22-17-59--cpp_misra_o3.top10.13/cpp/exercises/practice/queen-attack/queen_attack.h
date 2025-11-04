#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>
#include <iosfwd>   // forward declaration for std::ostream

namespace queen_attack {

using coordinate_type = int; // alias – raw type appears only here (MISRA-compliant)
using position_type   = std::pair<coordinate_type, coordinate_type>;

class chess_board {
public:
    chess_board(const position_type& white_pos,
                const position_type& black_pos);

    [[nodiscard]] position_type white() const noexcept;
    [[nodiscard]] position_type black() const noexcept;
    [[nodiscard]] bool          can_attack() const noexcept;

private:
    position_type m_white;
    position_type m_black;
};

std::ostream& operator<<(std::ostream& os, const chess_board& board);

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

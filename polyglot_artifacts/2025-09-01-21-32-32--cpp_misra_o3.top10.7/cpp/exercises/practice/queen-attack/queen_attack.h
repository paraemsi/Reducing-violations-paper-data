#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>
#include <stdexcept>

namespace queen_attack {

using coordinate_value_t = std::int32_t;                                  // fixed-width signed type
using coordinate_t       = std::pair<coordinate_value_t, coordinate_value_t>; // public interface (matches tests)
using storage_coordinate_t = std::pair<std::uint8_t, std::uint8_t>;           // internal storage

class chess_board {
public:
    chess_board(
        coordinate_t white = coordinate_t(0, 3),
        coordinate_t black = coordinate_t(7, 3));

    coordinate_t white() const noexcept;
    coordinate_t black() const noexcept;

    bool can_attack() const noexcept;

    explicit operator std::string() const;

private:
    storage_coordinate_t m_white;
    storage_coordinate_t m_black;

    static bool can_attack(const storage_coordinate_t& white_pos,
                           const storage_coordinate_t& black_pos) noexcept;
    static void validate_position(const coordinate_t& position);
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H

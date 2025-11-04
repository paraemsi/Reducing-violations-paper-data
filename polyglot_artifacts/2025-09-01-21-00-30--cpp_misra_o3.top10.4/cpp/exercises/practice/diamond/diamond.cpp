#include "diamond.h"

#include <cstdint>
#include <string>   // for std::char_traits
#include <sstream>
#include <stdexcept>

namespace diamond {

namespace {

/* Helper: return integer code-point of a character using char_traits */
constexpr DIAMOND_NODISCARD auto to_int(char ch) noexcept -> std::int32_t
{
    return std::char_traits<char>::to_int_type(ch);
}

/* Helper: return character from integer code-point using char_traits */
constexpr DIAMOND_NODISCARD auto to_char(std::int32_t code) noexcept -> char
{
    return std::char_traits<char>::to_char_type(code);
}

}  // namespace

auto create_diamond(char letter) -> std::vector<std::string>
{
    constexpr std::int32_t int_A { to_int('A') };
    constexpr std::int32_t int_Z { to_int('Z') };

    const std::int32_t int_letter { to_int(letter) };

    if((int_letter < int_A) || (int_letter > int_Z))
    {
        throw std::invalid_argument("letter must be in range 'A' .. 'Z'");
    }

    const std::int32_t max_idx { int_letter - int_A };
    const std::int32_t size { (max_idx * 2) + 1 };

    std::vector<std::string> rows;
    rows.reserve(static_cast<std::size_t>(size));

    for(std::int32_t r { 0 }; r < size; ++r)
    {
        const std::int32_t idx { (r <= max_idx) ? r : (size - 1) - r };
        const std::int32_t left_pad { max_idx - idx };
        const std::int32_t inner_spaces { (idx == 0) ? 0 : (idx * 2) - 1 };

        const char ch { to_char(int_A + idx) };

        std::string row(static_cast<std::size_t>(left_pad), ' ');
        row.push_back(ch);

        if(inner_spaces > 0)
        {
            row.append(static_cast<std::size_t>(inner_spaces), ' ');
            row.push_back(ch);
        }

        row.append(static_cast<std::size_t>(left_pad), ' ');
        rows.emplace_back(row);
    }

    return rows;
}

DIAMOND_NODISCARD auto rows(char letter) -> std::vector<std::string>
{
    return create_diamond(letter);
}

auto create_diamond_string(char letter) -> std::string
{
    const std::vector<std::string> rows { create_diamond(letter) };

    std::ostringstream oss;
    const std::size_t last { rows.size() - 1U };

    for(std::size_t i { 0U }; i < rows.size(); ++i)
    {
        oss << rows[i];
        if(i != last)
        {
            oss << '\n';
        }
    }

    return oss.str();
}

}  // namespace diamond

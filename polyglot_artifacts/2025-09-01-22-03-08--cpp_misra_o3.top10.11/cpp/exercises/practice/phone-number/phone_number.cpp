#include "phone_number.h"
#include <cstddef>
#include <stdexcept>

namespace phone_number {

namespace
{
/* Helper to ensure a character is one of the supplied options, using only
 * equality comparisons (MISRA rule compliance).
 */
constexpr bool char_in_set(char ch, const char* set, std::size_t len) noexcept
{
    for(std::size_t i{static_cast<std::size_t>(0)}; i < len; ++i)
    {
        if(ch == set[i])
        {
            return true;
        }
    }
    return false;
}
} // unnamed namespace

bool phone_number::is_digit(char ch) noexcept
{
    constexpr const char digits[] {'0', '1', '2', '3', '4',
                                   '5', '6', '7', '8', '9'};
    return char_in_set(ch, digits, static_cast<std::size_t>(10));
}

bool phone_number::is_valid_part_start(char ch) noexcept
{
    /* Valid leading digit for area/exchange code is 2-9. */
    constexpr const char allowed[] {'2', '3', '4', '5', '6', '7', '8', '9'};
    return char_in_set(ch, allowed, static_cast<std::size_t>(8));
}

phone_number::phone_number(std::string_view input)
    : m_number{}
{
    std::string digits;
    digits.reserve(input.size());

    /* Characters that may legally separate digits in the input. */
    constexpr const char allowed[] {' ', '+', '(', ')', '-', '.', '\t'};

    for(char ch : input)
    {
        if(is_digit(ch))
        {
            digits.push_back(ch);
        }
        else if(char_in_set(ch, allowed, static_cast<std::size_t>(7)))
        {
            /* separator character – ignore */
        }
        else
        {
            throw std::domain_error("invalid phone number");
        }
    }

    /* Remove NANP country code if present, otherwise validate 11-digit numbers. */
    if((digits.size() == static_cast<std::size_t>(11)) && (digits[0] == '1'))
    {
        digits.erase(static_cast<std::size_t>(0), static_cast<std::size_t>(1));
    }
    else if(digits.size() == static_cast<std::size_t>(11))
    {
        throw std::domain_error("invalid phone number");
    }

    /* The final digit count must be exactly 10. */
    if(digits.size() != static_cast<std::size_t>(10))
    {
        throw std::domain_error("invalid phone number");
    }

    /* Area code and exchange code may not start with 0 or 1. */
    if((!is_valid_part_start(digits[0])) || (!is_valid_part_start(digits[3])))
    {
        throw std::domain_error("invalid phone number");
    }

    m_number = digits;
}

std::string phone_number::number() const
{
    return m_number;
}

std::string phone_number::area_code() const
{
    return m_number.substr(static_cast<std::size_t>(0), static_cast<std::size_t>(3));
}

std::string phone_number::pretty() const
{
    return "(" + area_code() + ") "
         + m_number.substr(static_cast<std::size_t>(3), static_cast<std::size_t>(3))
         + "-" + m_number.substr(static_cast<std::size_t>(6));
}

}  // namespace phone_number

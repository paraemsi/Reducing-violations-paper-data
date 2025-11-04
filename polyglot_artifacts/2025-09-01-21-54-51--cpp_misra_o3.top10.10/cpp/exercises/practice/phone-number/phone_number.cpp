#include "phone_number.h"
#include <string>
#include <stdexcept>
#include <cstddef>
#include <string_view>
#include <locale>

namespace phone_number {

namespace
{
    constexpr bool is_digit_char(char ch) noexcept
    {
        auto const val {std::char_traits<char>::to_int_type(ch)};
        return ((val >= std::char_traits<char>::to_int_type('0')) &&
                (val <= std::char_traits<char>::to_int_type('9')));
    }
} // unnamed namespace

auto clean(const std::string& input) -> std::string
{
    std::string digits {};
    digits.reserve(input.size());

    for(char ch : input)
    {
        if(is_digit_char(ch) != false)
        {
            digits.push_back(ch);
        }
        else if((ch == ' ') || (ch == '.') || (ch == '-') || (ch == '(') || (ch == ')') || (ch == '+'))
        {
            /* permitted punctuation – skip it */
        }
        else
        {
            throw std::domain_error("letters or invalid characters not permitted");
        }
    }

    if((digits.size() != static_cast<std::size_t>(10U)) &&
       (digits.size() != static_cast<std::size_t>(11U)))
    {
        throw std::domain_error("incorrect number of digits");
    }

    if(digits.size() == static_cast<std::size_t>(11U))
    {
        if(digits.front() != '1')
        {
            throw std::domain_error("11-digit numbers must start with 1");
        }
        digits.erase(0U, 1U);
    }

    if((digits[0] == '0') || (digits[0] == '1'))
    {
        throw std::domain_error("area code cannot start with 0 or 1");
    }

    if((digits[3] == '0') || (digits[3] == '1'))
    {
        throw std::domain_error("exchange code cannot start with 0 or 1");
    }

    return digits;
}

/* ------------------------------------------------------------------ */
/*  phone_number class – thin wrapper around clean() utility          */
/* ------------------------------------------------------------------ */

phone_number::phone_number(const std::string& input)
    : m_number{clean(input)}
{
}

auto phone_number::number() const -> std::string
{
    return m_number;
}

auto phone_number::area_code() const -> std::string
{
    return m_number.substr(static_cast<std::string::size_type>(0U),
                           static_cast<std::string::size_type>(3U));
}

auto phone_number::pretty() const -> std::string
{
    return '(' + area_code() + ") " +
           m_number.substr(static_cast<std::string::size_type>(3U),
                           static_cast<std::string::size_type>(3U)) +
           '-' +
           m_number.substr(static_cast<std::string::size_type>(6U),
                           static_cast<std::string::size_type>(4U));
}

}  // namespace phone_number

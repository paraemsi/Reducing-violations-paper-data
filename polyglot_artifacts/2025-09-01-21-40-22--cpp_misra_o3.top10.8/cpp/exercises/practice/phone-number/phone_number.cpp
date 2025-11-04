#include <cstdint>
#include <locale>
#include <stdexcept>
#include <string>
#include "phone_number.h"

namespace phone_number {

namespace
{

/* Helper to check if a character is a decimal digit */
bool is_digit(char ch) noexcept
{
    return std::isdigit(static_cast<std::uint8_t>(ch), std::locale{});
}

/* Helper to verify that the first digit of an area/exchange code is between 2 and 9 */
bool is_valid_first_digit(char ch) noexcept
{
    const std::string allowed_digits{"23456789"};
    return allowed_digits.find(ch) != std::string::npos;
}

} // unnamed namespace

phone_number::phone_number(const std::string& input)
{
    std::string digits{};
    digits.reserve(input.size());

    for (char ch : input)
    {
        if (is_digit(ch))
        {
            digits.push_back(ch);
        }
    }

    if ((digits.size() == static_cast<std::size_t>(11U)) && (digits[0] == '1'))
    {
        digits.erase(0, static_cast<std::size_t>(1U));
    }

    bool valid{true};

    if (digits.size() != static_cast<std::size_t>(10U))
    {
        valid = false;
    }
    else if (!is_valid_first_digit(digits[0]))
    {
        valid = false;
    }
    else if (!is_valid_first_digit(digits[3]))
    {
        valid = false;
    }

    if (!valid)
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
    return m_number.substr(static_cast<std::size_t>(0U), static_cast<std::size_t>(3U));
}

std::string phone_number::pretty() const
{
    return "(" + area_code() + ") "
         + m_number.substr(static_cast<std::size_t>(3U), static_cast<std::size_t>(3U))
         + "-" + m_number.substr(static_cast<std::size_t>(6U), static_cast<std::size_t>(4U));
}

}  // namespace phone_number

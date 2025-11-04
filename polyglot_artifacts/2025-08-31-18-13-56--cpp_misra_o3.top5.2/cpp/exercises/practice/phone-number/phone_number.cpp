#include "phone_number.h"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <stdexcept>

namespace phone_number {

namespace
{
    // Returns 'true' if the supplied character is a decimal digit.
    inline bool is_valid_digit(char c) noexcept
    {
        return (std::isdigit(static_cast<unsigned char>(c)) != 0);
    }

    // Validates that the leading digit of an area/exchange code is 2‒9.
    inline bool first_digit_allowed(char c) noexcept
    {
        constexpr char allowed_chars[] = {'2', '3', '4', '5', '6', '7', '8', '9'};
        for (char allowed : allowed_chars)
        {
            if (allowed == c)
            {
                return true;
            }
        }
        return false;
    }
} // unnamed namespace

std::string phone_number::clean(const std::string& input)
{
    std::string digits{};
    digits.reserve(input.length());

    for (char c : input)
    {
        if (is_valid_digit(c))
        {
            digits.push_back(c);
        }
    }

    if ((digits.length() == static_cast<std::size_t>(11U)) &&
        (digits.front() == '1'))
    {
        digits.erase(0U, 1U);
    }

    if (digits.length() != static_cast<std::size_t>(10U))
    {
        throw std::domain_error("invalid number length");
    }

    if ((!first_digit_allowed(digits[0U])) ||
        (!first_digit_allowed(digits[3U])))
    {
        throw std::domain_error("invalid area or exchange code");
    }

    return digits;
}

phone_number::phone_number(const std::string& input) : digits_{clean(input)}
{
}

std::string phone_number::number() const noexcept
{
    return digits_;
}

std::string phone_number::area_code() const noexcept
{
    return digits_.substr(0U, 3U);
}

std::string phone_number::pretty() const noexcept
{
    return '(' + area_code() + ") " + digits_.substr(3U, 3U) + '-' +
           digits_.substr(6U, 4U);
}

} // namespace phone_number

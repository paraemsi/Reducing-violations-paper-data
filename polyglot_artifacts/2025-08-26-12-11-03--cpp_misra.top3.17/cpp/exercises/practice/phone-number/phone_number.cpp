#include "phone_number.h"
#include <string>
#include <cstdint>
#include <stdexcept>
#include <cctype>

namespace phone_number {

static std::string clean_digits(std::string const& input)
{
    std::string digits;
    digits.reserve(input.size());
    for (std::string::size_type i = 0U; i < input.size(); ++i)
    {
        char ch = input[i];
        if ((ch >= '0') && (ch <= '9'))
        {
            digits += ch;
        }
    }
    return digits;
}

phone_number::phone_number(std::string const& input)
{
    std::string digits = clean_digits(input);

    // Remove country code if present
    if ((digits.size() == static_cast<std::string::size_type>(11U)) && (digits[0] == '1'))
    {
        digits = digits.substr(1U, 10U);
    }

    // Validate length
    if (digits.size() != static_cast<std::string::size_type>(10U))
    {
        throw std::domain_error("Invalid phone number length");
    }

    // Validate area code and exchange code
    // Area code: digits[0], Exchange code: digits[3]
    if (((digits[0] < '2') || (digits[0] > '9')) ||
        ((digits[3] < '2') || (digits[3] > '9')))
    {
        throw std::domain_error("Invalid area or exchange code");
    }

    number_ = digits;
}

std::string phone_number::number() const
{
    return number_;
}

std::string phone_number::area_code() const
{
    return number_.substr(0U, 3U);
}

std::string phone_number::pretty() const
{
    return "(" + number_.substr(0U, 3U) + ") " +
           number_.substr(3U, 3U) + "-" +
           number_.substr(6U, 4U);
}

}  // namespace phone_number

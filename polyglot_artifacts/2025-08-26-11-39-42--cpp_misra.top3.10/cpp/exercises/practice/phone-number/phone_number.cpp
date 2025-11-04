#include "phone_number.h"
#include <string>
#include <cstdint>
#include <cctype>
#include <stdexcept>

namespace phone_number {

static std::string clean_number(const std::string& input)
{
    std::string digits;
    for (std::size_t i = 0U; i < input.length(); ++i)
    {
        char ch = input[i];
        if ((ch >= '0') && (ch <= '9'))
        {
            digits += ch;
        }
    }

    // Remove country code if present
    if ((digits.length() == static_cast<std::size_t>(11)) && (digits[0] == '1'))
    {
        digits = digits.substr(1U);
    }

    // Validate length and NANP rules
    if (digits.length() != static_cast<std::size_t>(10))
    {
        throw std::domain_error("Invalid phone number length");
    }

    // Area code and exchange code must start with 2-9
    if (((digits[0] < '2') || (digits[0] > '9')) ||
        ((digits[3] < '2') || (digits[3] > '9')))
    {
        throw std::domain_error("Invalid area or exchange code");
    }

    return digits;
}

phone_number::phone_number(const std::string& input)
    : m_number(clean_number(input))
{
}

std::string phone_number::number() const
{
    return m_number;
}

std::string phone_number::area_code() const
{
    return m_number.substr(0U, 3U);
}

std::string phone_number::pretty() const
{
    return "(" + m_number.substr(0U, 3U) + ") " +
           m_number.substr(3U, 3U) + "-" +
           m_number.substr(6U, 4U);
}

}  // namespace phone_number

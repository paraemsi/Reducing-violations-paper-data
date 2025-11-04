#include "phone_number.h"
#include <string>
#include <cstdint>
#include <stdexcept>
#include <cctype>

namespace phone_number {

namespace
{
    // Helper to check if a string is all digits
    bool is_all_digits(const std::string& s)
    {
        for (std::size_t i = 0U; i < s.size(); ++i)
        {
            if ((s[i] < '0') || (s[i] > '9'))
            {
                return false;
            }
        }
        return true;
    }
}

phone_number::phone_number(const std::string& input)
{
    std::string digits;
    digits.reserve(input.size());

    for (std::size_t i = 0U; i < input.size(); ++i)
    {
        char ch = input[i];
        if ((ch >= '0') && (ch <= '9'))
        {
            digits += ch;
        }
    }

    // Remove country code if present
    if ((digits.size() == 11U) && (digits[0] == '1'))
    {
        digits = digits.substr(1U);
    }

    // Must be exactly 10 digits
    if (digits.size() != 10U)
    {
        throw std::domain_error("Invalid phone number length");
    }

    // Area code and exchange code must start with 2-9
    if ((digits[0] < '2') || (digits[0] > '9'))
    {
        throw std::domain_error("Area code must start with 2-9");
    }
    if ((digits[3] < '2') || (digits[3] > '9'))
    {
        throw std::domain_error("Exchange code must start with 2-9");
    }

    m_number = digits;
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

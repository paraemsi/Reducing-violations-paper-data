#include "phone_number.h"
#include <string>
#include <cstdint>
#include <stdexcept>
#include <cctype>

namespace phone_number {

static std::string clean_number(const std::string& input)
{
    std::string digits;
    digits.reserve(input.size());

    for (std::size_t i = 0U; i < input.size(); ++i)
    {
        char ch = input[i];
        if ((ch >= '0') && (ch <= '9'))
        {
            digits.push_back(ch);
        }
    }

    // Remove country code if present
    if ((digits.size() == 11U) && (digits[0] == '1'))
    {
        digits = digits.substr(1U, 10U);
    }

    return digits;
}

phone_number::phone_number(const std::string& input)
{
    std::string digits = clean_number(input);

    // Validate length
    if (digits.size() != 10U)
    {
        throw std::domain_error("Invalid number of digits");
    }

    // Validate area code and exchange code
    // Area code: digits[0], Exchange code: digits[3]
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

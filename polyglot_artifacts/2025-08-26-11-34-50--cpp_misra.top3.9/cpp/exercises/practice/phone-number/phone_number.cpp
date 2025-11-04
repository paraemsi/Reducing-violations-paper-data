#include "phone_number.h"
#include <string>
#include <cstdint>
#include <stdexcept>
#include <cctype>

namespace phone_number {

namespace
{
    // Helper to check if a string is all digits
    bool is_all_digits(std::string const& s)
    {
        for (char c : s)
        {
            if ((c < '0') || (c > '9'))
            {
                return false;
            }
        }
        return true;
    }
}

std::string clean(std::string const& input)
{
    std::string digits;
    digits.reserve(input.size());
    for (std::string::size_type i = 0U; i < input.size(); ++i)
    {
        char c = input[i];
        if ((c >= '0') && (c <= '9'))
        {
            digits += c;
        }
    }

    // Remove country code if present
    if ((digits.size() == 11U) && (digits[0] == '1'))
    {
        digits = digits.substr(1U, 10U);
    }

    return digits;
}

phone_number::phone_number(std::string const& input)
{
    std::string digits;
    digits.reserve(input.size());
    for (std::string::size_type i = 0U; i < input.size(); ++i)
    {
        char c = input[i];
        if ((c >= '0') && (c <= '9'))
        {
            digits += c;
        }
    }

    // Remove country code if present
    if ((digits.size() == 11U) && (digits[0] == '1'))
    {
        digits = digits.substr(1U, 10U);
    }

    // Validation
    if (digits.size() != 10U)
    {
        throw std::domain_error("Invalid number of digits");
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
    // All must be digits
    if (!is_all_digits(digits))
    {
        throw std::domain_error("Non-digit in phone number");
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

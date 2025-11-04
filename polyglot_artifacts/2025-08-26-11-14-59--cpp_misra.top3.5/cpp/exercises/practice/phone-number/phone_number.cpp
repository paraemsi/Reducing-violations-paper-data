#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>

namespace phone_number {

static std::string only_digits(const std::string& input)
{
    std::string digits;
    for (std::size_t i = 0U; i < input.size(); ++i)
    {
        const char ch = input[i];
        if ((ch >= '0') && (ch <= '9'))
        {
            digits += ch;
        }
    }
    return digits;
}

phone_number::phone_number(const phone_str_t& input)
{
    phone_str_t digits = only_digits(input);

    // Remove country code if present
    if ((digits.size() == 11U) && (digits[0] == '1'))
    {
        digits = digits.substr(1U);
    }

    // Validate length
    if (digits.size() != 10U)
    {
        throw std::domain_error("Invalid phone number length");
    }

    // Validate area code and exchange code
    // Area code: digits[0], Exchange code: digits[3]
    if ((digits[0] < '2') || (digits[0] > '9'))
    {
        throw std::domain_error("Invalid area code");
    }
    if ((digits[3] < '2') || (digits[3] > '9'))
    {
        throw std::domain_error("Invalid exchange code");
    }

    m_number = digits;
}

phone_str_t phone_number::number() const
{
    return m_number;
}

phone_str_t phone_number::area_code() const
{
    return m_number.substr(0U, 3U);
}

phone_str_t phone_number::pretty() const
{
    return "(" + m_number.substr(0U, 3U) + ") " +
           m_number.substr(3U, 3U) + "-" +
           m_number.substr(6U, 4U);
}

}  // namespace phone_number

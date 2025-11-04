#include "phone_number.h"
#include <cctype>
#include <stdexcept>
#include <sstream>

namespace phone_number {

static std::string clean_number(const std::string& input)
{
    std::string digits;
    for (const char ch : input)
    {
        if ((ch >= '0') && (ch <= '9'))
        {
            digits += ch;
        }
    }

    // Remove country code if present
    if ((digits.length() == static_cast<std::size_t>(11U)) && (digits[0] == '1'))
    {
        digits = digits.substr(1U);
    }

    return digits;
}

phone_number::phone_number(const std::string& input)
{
    std::string digits = clean_number(input);

    // Validate length
    if (digits.length() != static_cast<std::size_t>(10U))
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
    std::ostringstream oss;
    oss << "(" << m_number.substr(0U, 3U) << ") "
        << m_number.substr(3U, 3U) << "-"
        << m_number.substr(6U, 4U);
    return oss.str();
}

}  // namespace phone_number

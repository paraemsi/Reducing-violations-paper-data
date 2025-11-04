#include "phone_number.h"
#include <cctype>
#include <stdexcept>
#include <sstream>

namespace phone_number {

static std::string only_digits(const std::string& input)
{
    std::string digits;
    for (const char ch : input)
    {
        if ((ch >= '0') && (ch <= '9'))
        {
            digits += ch;
        }
    }
    return digits;
}

static bool is_valid(const std::string& digits)
{
    if (digits.length() != 10U)
    {
        return false;
    }
    // Area code and exchange code must start with 2-9
    if ((digits[0] < '2') || (digits[0] > '9'))
    {
        return false;
    }
    if ((digits[3] < '2') || (digits[3] > '9'))
    {
        return false;
    }
    return true;
}

phone_number::phone_number(const std::string& input)
{
    std::string digits = only_digits(input);

    if ((digits.length() == 11U) && (digits[0] == '1'))
    {
        digits = digits.substr(1U);
    }

    if (!is_valid(digits))
    {
        throw std::domain_error("Invalid phone number");
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

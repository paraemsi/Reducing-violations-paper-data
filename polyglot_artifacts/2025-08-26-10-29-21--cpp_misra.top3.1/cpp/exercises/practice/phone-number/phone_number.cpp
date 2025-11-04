#include "phone_number.h"
#include <cctype>
#include <stdexcept>

namespace phone_number {

static phone_string_t clean(const phone_string_t& input)
{
    phone_string_t digits;
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

static bool is_valid(const phone_string_t& digits)
{
    if (digits.length() != static_cast<std::size_t>(10U))
    {
        return false;
    }
    // Area code and exchange code must start with 2-9
    if (((digits[0] < '2') || (digits[0] > '9')) ||
        ((digits[3] < '2') || (digits[3] > '9')))
    {
        return false;
    }
    return true;
}

phone_number::phone_number(const phone_string_t& input)
{
    phone_string_t digits = clean(input);
    if (!is_valid(digits))
    {
        throw std::domain_error("invalid phone number");
    }
    m_number = digits;
}

phone_string_t phone_number::number() const
{
    return m_number;
}

phone_string_t phone_number::area_code() const
{
    return m_number.substr(0U, 3U);
}

phone_string_t phone_number::pretty() const
{
    return "(" + m_number.substr(0U, 3U) + ") " +
           m_number.substr(3U, 3U) + "-" +
           m_number.substr(6U, 4U);
}

}  // namespace phone_number

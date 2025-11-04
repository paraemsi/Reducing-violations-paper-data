#include "phone_number.h"
#include <string>
#include <cstdint>
#include <cctype>
#include <stdexcept>
#include "phone_number.h"

namespace phone_number {

static phone_string_t clean(const phone_string_t& input)
{
    phone_string_t digits;
    for (std::size_t i = 0U; i < input.length(); ++i)
    {
        char ch = input[i];
        if ((ch >= '0') && (ch <= '9'))
        {
            digits += ch;
        }
    }
    if ((digits.length() == 11U) && (digits[0] == '1'))
    {
        digits = digits.substr(1U, 10U);
    }
    else if (digits.length() == 10U)
    {
        // ok
    }
    else
    {
        throw std::domain_error("invalid number of digits");
    }
    // Area code and exchange code validation
    if (((digits[0] < '2') || (digits[0] > '9')) ||
        ((digits[3] < '2') || (digits[3] > '9')))
    {
        throw std::domain_error("invalid area or exchange code");
    }
    return digits;
}

phone_number::phone_number(const phone_string_t& input)
    : m_number(clean(input))
{
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

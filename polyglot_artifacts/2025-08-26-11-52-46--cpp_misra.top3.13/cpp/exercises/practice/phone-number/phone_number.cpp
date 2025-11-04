#include "phone_number.h"
#include <string>
#include <cstdint>
#include <cctype>
#include <stdexcept>

namespace phone_number {

namespace
{
    // Helper to clean and validate NANP phone numbers
    phone_string_t clean_number(const phone_string_t& input)
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

        // Remove country code if present
        if ((digits.length() == 11U) && (digits[0] == '1'))
        {
            digits = digits.substr(1U);
        }

        // Must be exactly 10 digits
        if (digits.length() != 10U)
        {
            throw std::domain_error("Invalid phone number length");
        }

        // Area code and exchange code must start with 2-9
        if ((digits[0] < '2') || (digits[0] > '9'))
        {
            throw std::domain_error("Invalid area code");
        }
        if ((digits[3] < '2') || (digits[3] > '9'))
        {
            throw std::domain_error("Invalid exchange code");
        }

        return digits;
    }
}

phone_number::phone_number(const phone_string_t& input)
    : m_number(clean_number(input))
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

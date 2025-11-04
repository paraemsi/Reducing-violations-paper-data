#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>

namespace phone_number {

namespace
{
    std::string clean_number(const std::string& input)
    {
        std::string digits;
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
            throw std::domain_error("Invalid area code");
        }
        if ((digits[3] < '2') || (digits[3] > '9'))
        {
            throw std::domain_error("Invalid exchange code");
        }

        return digits;
    }
}

phone_number::phone_number(const std::string& input)
    : number_(clean_number(input))
{
}

std::string phone_number::number() const
{
    return number_;
}

std::string phone_number::area_code() const
{
    return number_.substr(0U, 3U);
}

std::string phone_number::pretty() const
{
    return "(" + number_.substr(0U, 3U) + ") " +
           number_.substr(3U, 3U) + "-" +
           number_.substr(6U, 4U);
}

}  // namespace phone_number

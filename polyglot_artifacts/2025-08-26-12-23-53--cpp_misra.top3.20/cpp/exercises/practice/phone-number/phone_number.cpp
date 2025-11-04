#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>

namespace phone_number {

namespace
{
    // Helper to check if a digit is valid for N (2-9)
    bool is_valid_N(char ch)
    {
        return (ch >= '2') && (ch <= '9');
    }
}

phone_number::phone_number(const phone_str_t& input)
    : number_ {}
{
    phone_str_t digits {};
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

    if (digits.length() != static_cast<std::size_t>(10U))
    {
        throw std::domain_error("Invalid number of digits");
    }

    // Area code and exchange code must start with 2-9
    if ((!is_valid_N(digits[0])) || (!is_valid_N(digits[3])))
    {
        throw std::domain_error("Invalid area or exchange code");
    }

    number_ = digits;
}

auto phone_number::number() const -> phone_str_t
{
    return number_;
}

}  // namespace phone_number

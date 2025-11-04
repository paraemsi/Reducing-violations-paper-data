#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>

namespace phone_number {

namespace
{
    // Helper to check if a string is all digits
    bool is_all_digits(const std::string& s)
    {
        for (std::string::size_type i = 0U; i < s.size(); ++i)
        {
            if ((s[i] < '0') || (s[i] > '9'))
            {
                return false;
            }
        }
        return true;
    }
}

phone_number::phone_number(const std::string& input)
{
    std::string digits;
    digits.reserve(input.size());
    for (std::string::size_type i = 0U; i < input.size(); ++i)
    {
        const char ch = input[i];
        if ((ch >= '0') && (ch <= '9'))
        {
            digits.push_back(ch);
        }
    }

    // Remove country code if present
    if ((digits.size() == static_cast<std::string::size_type>(11U)) && (digits[0] == '1'))
    {
        digits = digits.substr(1U, 10U);
    }

    // Validation: must be exactly 10 digits
    if (digits.size() != static_cast<std::string::size_type>(10U))
    {
        throw std::domain_error("Invalid phone number: must have 10 digits");
    }

    // Area code and exchange code validation
    // Area code: digits[0], Exchange code: digits[3]
    if ((digits[0] < '2') || (digits[0] > '9'))
    {
        throw std::domain_error("Invalid area code");
    }
    if ((digits[3] < '2') || (digits[3] > '9'))
    {
        throw std::domain_error("Invalid exchange code");
    }

    number_ = digits;
}

auto phone_number::number() const -> std::string
{
    return number_;
}

auto phone_number::area_code() const -> std::string
{
    return number_.substr(0U, 3U);
}

auto phone_number::pretty() const -> std::string
{
    return "(" + number_.substr(0U, 3U) + ") " + number_.substr(3U, 3U) + "-" + number_.substr(6U, 4U);
}

}  // namespace phone_number

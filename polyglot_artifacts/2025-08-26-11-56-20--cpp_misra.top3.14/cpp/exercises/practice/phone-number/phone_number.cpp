#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>

namespace phone_number {

namespace
{
    auto clean_digits(const std::string& input) -> std::string
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
        return digits;
    }

    auto is_valid(const std::string& digits) -> bool
    {
        if (digits.size() != static_cast<std::string::size_type>(10U))
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
}

phone_number::phone_number(const std::string& input)
{
    std::string digits = clean_digits(input);

    // Remove country code if present
    if ((digits.size() == static_cast<std::string::size_type>(11U)) && (digits[0] == '1'))
    {
        digits = digits.substr(1U, 10U);
    }

    if (!is_valid(digits))
    {
        throw std::domain_error("Invalid phone number");
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
    return "(" + number_.substr(0U, 3U) + ") " +
           number_.substr(3U, 3U) + "-" +
           number_.substr(6U, 4U);
}

}  // namespace phone_number

#include "phone_number.h"
#include <string>
#include <cstdint>
#include <stdexcept>
#include <cctype>

namespace phone_number {

static phone_string_t only_digits(const phone_string_t& input)
{
    phone_string_t digits;
    digits.reserve(input.size());
    for (std::size_t i = 0U; i < input.size(); ++i)
    {
        char ch = input[i];
        if ((ch >= '0') && (ch <= '9'))
        {
            digits.push_back(ch);
        }
    }
    return digits;
}

static bool is_valid_area(const phone_string_t& digits)
{
    // Area code: NXX, N=2-9, X=0-9
    return ((digits[0] >= '2') && (digits[0] <= '9'));
}

static bool is_valid_exchange(const phone_string_t& digits)
{
    // Exchange code: NXX, N=2-9, X=0-9
    return ((digits[3] >= '2') && (digits[3] <= '9'));
}

phone_number::phone_number(const phone_string_t& input)
{
    phone_string_t digits = only_digits(input);

    if ((digits.size() == 11U) && (digits[0] == '1'))
    {
        digits = digits.substr(1U);
    }
    else if (digits.size() == 11U)
    {
        throw std::domain_error("11 digits must start with 1");
    }

    if (digits.size() != 10U)
    {
        throw std::domain_error("Phone number must be 10 digits");
    }

    if (!is_valid_area(digits))
    {
        throw std::domain_error("Area code must start with 2-9");
    }
    if (!is_valid_exchange(digits))
    {
        throw std::domain_error("Exchange code must start with 2-9");
    }

    number_ = digits;
}

phone_string_t phone_number::number() const
{
    return number_;
}

phone_string_t phone_number::area_code() const
{
    return number_.substr(0U, 3U);
}

phone_string_t phone_number::pretty() const
{
    return "(" + number_.substr(0U, 3U) + ") " + number_.substr(3U, 3U) + "-" + number_.substr(6U, 4U);
}

}  // namespace phone_number

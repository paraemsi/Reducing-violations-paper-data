#include "phone_number.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <cstdint>
#include <stdexcept>
#include <string>

namespace phone_number {

std::string clean(const std::string& input)
{
    std::string digits;
    digits.reserve(input.size());

    for (char ch : input)
    {
        const auto int_val =
            std::char_traits<char>::to_int_type(ch); /* convert via helper */
        if (std::isdigit(int_val) != 0)
        {
            digits.push_back(ch);
        }
    }

    /* Remove leading country code ‘1’ if present */
    if ((digits.size() == static_cast<std::size_t>(11U)) &&
        (digits.front() == '1'))
    {
        digits.erase(digits.begin());
    }

    if (digits.size() != static_cast<std::size_t>(10U))
    {
        throw std::invalid_argument("Invalid phone number: incorrect length");
    }

    static const std::array<char, 8U> allowed_first_digits{
        {'2', '3', '4', '5', '6', '7', '8', '9'}};

    const auto is_allowed_first_digit =
        [&](char digit) -> bool
    {
        return std::find(
                   allowed_first_digits.begin(),
                   allowed_first_digits.end(),
                   digit) != allowed_first_digits.end();
    };

    if ((!is_allowed_first_digit(digits[0])) ||
        (!is_allowed_first_digit(digits[3])))
    {
        throw std::invalid_argument(
            "Invalid phone number: improper area or exchange code");
    }

    return digits;
}

/*----------------------------------------------------------------------------*/
/*  phone_number member-function definitions                                  */
/*----------------------------------------------------------------------------*/
phone_number::phone_number::phone_number(const std::string& input)
    : digits_{clean(input)}
{
}

auto phone_number::phone_number::number() const -> std::string
{
    return digits_;
}

auto phone_number::phone_number::area_code() const -> std::string
{
    return digits_.substr(static_cast<std::size_t>(0U),
                          static_cast<std::size_t>(3U));
}

auto phone_number::phone_number::pretty() const -> std::string
{
    return "(" + area_code() + ") " +
           digits_.substr(static_cast<std::size_t>(3U),
                          static_cast<std::size_t>(3U)) + "-" +
           digits_.substr(static_cast<std::size_t>(6U));
}

}  // namespace phone_number

#include "phone_number.h"

#include <cctype>
#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <string>

namespace phone_number {

auto clean(const std::string& raw) -> std::string
{
    std::string digits;
    digits.reserve(raw.length());

    for (char ch : raw)
    {
        if (std::isdigit(static_cast<int>(static_cast<std::uint8_t>(ch))) != 0)
        {
            digits.push_back(ch);
        }
    }

    /* Remove leading country code ‘1’ if present */
    if ((digits.size() == static_cast<std::size_t>(11U)) && (digits[0] == '1'))
    {
        digits.erase(0U, 1U);
    }

    if (digits.size() != static_cast<std::size_t>(10U))
    {
        throw std::domain_error("invalid number of digits");
    }

    /* Validate area code — must start with 2-9 */
    if ((digits[0] == '0') || (digits[0] == '1'))
    {
        throw std::domain_error("invalid area code");
    }

    /* Validate exchange code — must start with 2-9 */
    if ((digits[3] == '0') || (digits[3] == '1'))
    {
        throw std::domain_error("invalid exchange code");
    }

    return digits;
}

/* ------------------------------------------------------------------------- */
/*  phone_number class wrappers                                              */
/* ------------------------------------------------------------------------- */

phone_number::phone_number(const std::string& raw)
    : digits_{ clean(raw) } /* May throw std::domain_error */
{
}

auto phone_number::number() const -> std::string
{
    return digits_;
}

auto phone_number::area_code() const -> std::string
{
    /* digits_ contains exactly ten digits, validated by clean() */
    return digits_.substr(0U, 3U);
}

auto phone_number::pretty() const -> std::string
{
    /* Format: (AAA) BBB-CCCC */
    return '(' + digits_.substr(0U, 3U) + ") " +
           digits_.substr(3U, 3U) + '-' +
           digits_.substr(6U, 4U);
}

}  // namespace phone_number

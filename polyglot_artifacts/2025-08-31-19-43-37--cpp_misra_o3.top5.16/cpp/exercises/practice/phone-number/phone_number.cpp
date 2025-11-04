#include "phone_number.h"
#include <stdexcept>
#include <cstddef>

namespace phone_number {

auto clean(const std::string& input) -> std::string
{
    const std::string digits{ "0123456789" };
    const std::string punctuation{ " .()-+" };

    std::string digits_only{};
    digits_only.reserve(input.size());

    for (const char ch : input)
    {
        /* Keep numeric characters, ignore benign punctuation, reject the rest */
        if (digits.find(ch) != std::string::npos)
        {
            digits_only.push_back(ch);
        }
        else if (punctuation.find(ch) != std::string::npos)
        {
            /* skip */
        }
        else
        {
            return std::string{};     /* Invalid character */
        }
    }

    /* Handle an optional leading country code ‘1’ */
    if (digits_only.length() == static_cast<std::size_t>(11))
    {
        if (digits_only.front() == '1')
        {
            digits_only.erase(0U, 1U);
        }
        else
        {
            return std::string{};     /* 11 digits but does not start with 1 */
        }
    }

    /* Must now contain exactly ten digits */
    if (digits_only.length() != static_cast<std::size_t>(10))
    {
        return std::string{};
    }

    /* Helper to verify a leading digit is 2-9 (without relational operators) */
    const auto is_valid_leading_digit =
        [](const char c) noexcept -> bool
        {
            return ((c == '2') || (c == '3') || (c == '4') || (c == '5') ||
                    (c == '6') || (c == '7') || (c == '8') || (c == '9'));
        };

    /* Area code and exchange code must both start with 2-9 */
    if ((!is_valid_leading_digit(digits_only[0])) ||
        (!is_valid_leading_digit(digits_only[3])))
    {
        return std::string{};
    }

    return digits_only;
}

/*----------------------------------------------------------------------------*/
/*                phone_number  class implementation                          */
/*----------------------------------------------------------------------------*/

phone_number::phone_number(const std::string& input)
    : digits_{ /* NOLINT(cppcoreguidelines-prefer-member-initializer) */
        clean(input) }
{
    if (digits_.empty())
    {
        throw std::domain_error("invalid phone number");
    }
}

auto phone_number::number() const -> std::string
{
    return digits_;
}

auto phone_number::area_code() const -> std::string
{
    return digits_.substr(0U, 3U);
}

auto phone_number::pretty() const -> std::string
{
    return "(" + area_code() + ") " + digits_.substr(3U, 3U) + "-" +
           digits_.substr(6U, 4U);
}

}  // namespace phone_number

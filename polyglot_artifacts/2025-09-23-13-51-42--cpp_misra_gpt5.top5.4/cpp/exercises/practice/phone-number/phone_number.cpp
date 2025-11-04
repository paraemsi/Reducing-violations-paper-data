#include "phone_number.h"

#include <string>
#include <cstddef>
#include <stdexcept>

namespace {
    // Returns true if ch is one of the ASCII digits '0'..'9'.
    // Uses only equality comparisons to avoid relying on character numeric values.
    bool is_digit_char(char ch)
    {
        return ((ch == '0') || (ch == '1') || (ch == '2') || (ch == '3') || (ch == '4') || (ch == '5') || (ch == '6') || (ch == '7') || (ch == '8') || (ch == '9'));
    }

    // Returns true if ch is an allowed separator character in phone numbers.
    // Allowed: space, '(', ')', '-', '.', '+'.
    bool is_allowed_separator(char ch)
    {
        return ((ch == ' ') || (ch == '(') || (ch == ')') || (ch == '-') || (ch == '.') || (ch == '+'));
    }
}

namespace phone_number {

[[nodiscard]] std::string clean(const std::string& input)
{
    std::string digits{};
    digits.reserve(input.size());

    for (char ch : input)
    {
        if (is_digit_char(ch))
        {
            digits.push_back(ch);
        }
        else if (is_allowed_separator(ch))
        {
            // ignore allowed separator characters
        }
        else
        {
            throw std::domain_error("invalid character in phone number");
        }
    }

    if ((digits.size() == static_cast<std::size_t>(11)) && (digits[0] == '1'))
    {
        digits.erase(static_cast<std::size_t>(0), static_cast<std::size_t>(1));
    }

    return digits;
}

phone_number::phone_number(const std::string& input)
    : digits_{}
{
    const std::string cleaned{ clean(input) };

    if (cleaned.size() != static_cast<std::size_t>(10))
    {
        throw std::domain_error("invalid phone number length");
    }

    // Area code must not start with 0 or 1
    if ((cleaned[0] == '0') || (cleaned[0] == '1'))
    {
        throw std::domain_error("invalid area code");
    }

    // Exchange code must not start with 0 or 1
    if ((cleaned[3] == '0') || (cleaned[3] == '1'))
    {
        throw std::domain_error("invalid exchange code");
    }

    digits_ = cleaned;
}

[[nodiscard]] std::string phone_number::number() const
{
    return digits_;
}

[[nodiscard]] std::string phone_number::area_code() const
{
    return digits_.substr(static_cast<std::size_t>(0), static_cast<std::size_t>(3));
}

[[nodiscard]] std::string phone_number::pretty() const
{
    const std::string area{ digits_.substr(static_cast<std::size_t>(0), static_cast<std::size_t>(3)) };
    const std::string exch{ digits_.substr(static_cast<std::size_t>(3), static_cast<std::size_t>(3)) };
    const std::string sub{ digits_.substr(static_cast<std::size_t>(6), static_cast<std::size_t>(4)) };

    std::string out{};
    out.reserve(static_cast<std::size_t>(16));
    out.push_back('(');
    out += area;
    out.push_back(')');
    out.push_back(' ');
    out += exch;
    out.push_back('-');
    out += sub;
    return out;
}

}  // namespace phone_number

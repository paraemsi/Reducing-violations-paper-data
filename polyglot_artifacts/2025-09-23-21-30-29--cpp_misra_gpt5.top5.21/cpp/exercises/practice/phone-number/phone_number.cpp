#include "phone_number.h"

#include <cctype>
#include <stdexcept>
#include <string>

namespace {
auto is_nxx_digit(char ch) -> bool
{
    return (ch == '2') || (ch == '3') || (ch == '4') || (ch == '5') || (ch == '6') || (ch == '7') || (ch == '8') || (ch == '9');
}
}

namespace phone_number {

auto clean(const std::string& raw) -> std::string
{
    std::string digits;
    digits.reserve(raw.size());

    for (const char ch : raw)
    {
        const std::char_traits<char>::int_type ch_val = std::char_traits<char>::to_int_type(ch);
        if (std::isdigit(ch_val) != 0)
        {
            digits.push_back(ch);
        }
        else
        {
            // Ignore non-digit characters
        }
    }

    if ((digits.size() == static_cast<std::string::size_type>(11)) && (digits[0] == '1'))
    {
        digits.erase(static_cast<std::string::size_type>(0), static_cast<std::string::size_type>(1));
    }
    else
    {
        // No country code to strip
    }

    if (digits.size() != static_cast<std::string::size_type>(10))
    {
        throw std::domain_error("invalid NANP number length");
    }
    else
    {
        // Valid 10-digit number
    }

    // Validate NANP NXX rules: area code and exchange code must start with 2-9
    if ((is_nxx_digit(digits[0]) == false) || (is_nxx_digit(digits[3]) == false))
    {
        throw std::domain_error("invalid NANP area or exchange code");
    }
    else
    {
        // Valid NXX positions
    }

    return digits;
}

phone_number::phone_number(const std::string& raw) : digits_(clean(raw))
{
}

auto phone_number::number() const -> std::string
{
    return digits_;
}

auto phone_number::area_code() const -> std::string
{
    return digits_.substr(static_cast<std::string::size_type>(0), static_cast<std::string::size_type>(3));
}

auto phone_number::pretty() const -> std::string
{
    const std::string exchange = digits_.substr(static_cast<std::string::size_type>(3), static_cast<std::string::size_type>(3));
    const std::string subscriber = digits_.substr(static_cast<std::string::size_type>(6), static_cast<std::string::size_type>(4));
    return "(" + area_code() + ") " + exchange + "-" + subscriber;
}

}  // namespace phone_number

#include "phone_number.h"
#include <cctype>
#include <stdexcept>
#include <string>
#include <cstdint>

namespace phone_number {

std::string clean(const std::string& input)
{
    std::string digits {};
    digits.reserve(input.size());

    for (char ch : input) {
        if (std::isdigit(std::char_traits<char>::to_int_type(ch)) != 0) {
            digits.push_back(ch);
        } else if ((ch == '+') || (ch == ' ') || (ch == '-') ||
                   (ch == '(') || (ch == ')') || (ch == '.')) {
            continue;
        } else {
            throw std::domain_error("invalid character");
        }
    }

    if ((digits.size() == 11U) && (digits[0] == '1')) {
        digits.erase(0U, 1U);
    }

    if (digits.size() != 10U) {
        throw std::domain_error("incorrect number of digits");
    }

    if ((digits[0] == '0') || (digits[0] == '1')) {
        throw std::domain_error("invalid area code");
    }

    if ((digits[3] == '0') || (digits[3] == '1')) {
        throw std::domain_error("invalid exchange code");
    }

    return digits;
}

phone_number::phone_number(const std::string& input) : digits_(clean(input))
{
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
    return std::string{"("} + digits_.substr(0U, 3U) + ") " +
           digits_.substr(3U, 3U) + "-" + digits_.substr(6U, 4U);
}

} // namespace phone_number

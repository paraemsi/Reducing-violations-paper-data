#include "phone_number.h"

#include <cctype>
#include <string>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& input)
    : cleaned_("0000000000")
{
    if (contains_alpha(input)) {
        throw std::domain_error("letters not permitted");
    }

    std::string digits = only_digits(input);

    if ((digits.size()) == 11U) {
        if ((digits[0] == '1')) {
            digits = digits.substr(1U);
        } else {
            throw std::domain_error("11 digits must start with 1");
        }
    }

    if ((digits.size()) != 10U) {
        throw std::domain_error("incorrect number of digits");
    }

    if (!valid_nxx_rules(digits)) {
        throw std::domain_error("invalid area or exchange code");
    }

    cleaned_ = digits;
}

std::string phone_number::number() const
{
    return cleaned_;
}

std::string phone_number::area_code() const
{
    return cleaned_.substr(0U, 3U);
}

std::string phone_number::pretty() const
{
    const std::string ac = area_code();
    const std::string ex = cleaned_.substr(3U, 3U);
    const std::string sub = cleaned_.substr(6U, 4U);

    return (((((std::string("(") + ac) + std::string(") ")) + ex) + std::string("-")) + sub);
}

bool phone_number::contains_alpha(const std::string& s) noexcept
{
    for (char ch : s) {
        if ((std::isalpha(std::char_traits<char>::to_int_type(ch))) != 0) {
            return true;
        }
    }
    return false;
}

std::string phone_number::only_digits(const std::string& s)
{
    std::string result;
    result.reserve(s.size());
    for (char ch : s) {
        if ((std::isdigit(std::char_traits<char>::to_int_type(ch))) != 0) {
            result.push_back(ch);
        }
    }
    return result;
}

bool phone_number::valid_nxx_rules(const std::string& digits) noexcept
{
    if ((digits.size()) != 10U) {
        return false;
    }

    if ((digits[0] == '0') || (digits[0] == '1')) {
        return false;
    }

    if ((digits[3] == '0') || (digits[3] == '1')) {
        return false;
    }

    return true;
}

}  // namespace phone_number

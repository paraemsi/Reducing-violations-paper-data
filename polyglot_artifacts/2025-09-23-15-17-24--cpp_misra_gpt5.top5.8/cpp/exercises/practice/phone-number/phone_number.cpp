#include "phone_number.h"

#include <cctype>
#include <cstdint>
#include <stdexcept>
#include <string>

namespace phone_number {

std::string clean_number(const std::string& input)
{
    std::string digits;
    digits.reserve(input.size());

    for (const char ch : input) {
        const int cval = std::char_traits<char>::to_int_type(ch);
        if ((std::isalpha(cval) != 0)) {
            throw std::domain_error("letters not permitted");
        } else if ((std::isdigit(cval) != 0)) {
            digits.push_back(ch);
        } else if ((ch == ' ') || (ch == '-') || (ch == '.') || (ch == '(') || (ch == ')') || (ch == '+')) {
            // allowed separators; ignore
        } else {
            throw std::domain_error("punctuation not permitted");
        }
    }

    if (digits.size() == 11U) {
        if (digits.front() != '1') {
            throw std::domain_error("11 digits must start with 1");
        } else {
            digits = digits.substr(1U);
        }
    } else if (digits.size() == 10U) {
        // ok
    } else {
        throw std::domain_error("incorrect number of digits");
    }

    // Validate NANP rules: area code and exchange code cannot start with 0 or 1
    if ((digits.size() >= 1U) && ((digits[0] == '0') || (digits[0] == '1'))) {
        throw std::domain_error("area code cannot start with 0 or 1");
    }
    if ((digits.size() >= 4U) && ((digits[3] == '0') || (digits[3] == '1'))) {
        throw std::domain_error("exchange code cannot start with 0 or 1");
    }

    return digits;
}

phone_number::phone_number(const std::string& input)
    : digits_(clean_number(input))
{
}

std::string phone_number::number() const
{
    return digits_;
}

std::string phone_number::area_code() const
{
    if (digits_.size() >= 3U) {
        return digits_.substr(0U, 3U);
    } else {
        return std::string{};
    }
}

std::string phone_number::to_string() const
{
    if (digits_.size() >= 10U) {
        const std::string area = digits_.substr(0U, 3U);
        const std::string exchange = digits_.substr(3U, 3U);
        const std::string subscriber = digits_.substr(6U, 4U);
        return std::string("(") + area + std::string(") ") + exchange + std::string("-") + subscriber;
    } else {
        return digits_;
    }
}

std::string phone_number::pretty() const
{
    return to_string();
}

}  // namespace phone_number

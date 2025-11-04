#include "phone_number.h"

#include <cctype>
#include <cstdint>
#include <string>
#include <string_view>
#include <stdexcept>

namespace {

inline bool is_alpha_char(char ch) {
    return (std::isalpha(static_cast<int>(static_cast<std::uint8_t>(ch))) != 0);
}

inline bool is_digit_char(char ch) {
    return (std::isdigit(static_cast<int>(static_cast<std::uint8_t>(ch))) != 0);
}

inline bool is_allowed_separator(char ch) {
    switch (ch) {
        case ' ':
        case '(':
        case ')':
        case '.':
        case '-':
        case '+':
            return true;
        default:
            return false;
    }
}

}  // unnamed namespace

namespace phone_number {

phone_number::phone_number(const std::string& input)
    : m_number("0000000000")
{
    std::string digits;
    digits.reserve(input.size());

    for (char ch : input) {
        if (is_alpha_char(ch)) {
            throw std::domain_error("letters not permitted");
        } else {
            if (is_digit_char(ch)) {
                digits.push_back(ch);
            } else {
                if (is_allowed_separator(ch)) {
                    // permitted separator; ignore
                } else {
                    throw std::domain_error("punctuations not permitted");
                }
            }
        }
    }

    if (digits.size() == static_cast<std::size_t>(11)) {
        if (digits[0] == '1') {
            digits.erase(0, static_cast<std::size_t>(1));
        } else {
            throw std::domain_error("11 digits must start with 1");
        }
    } else {
        if (digits.size() == static_cast<std::size_t>(10)) {
            // ok
        } else {
            throw std::domain_error("incorrect number of digits");
        }
    }

    const char area_first = digits[0];
    const char exchange_first = digits[3];

    const bool area_ok = ((area_first != '0') && (area_first != '1'));
    const bool exchange_ok = ((exchange_first != '0') && (exchange_first != '1'));

    if (area_ok && exchange_ok) {
        m_number = digits;
    } else {
        if (!area_ok) {
            throw std::domain_error("area code cannot start with 0 or 1");
        } else {
            throw std::domain_error("exchange code cannot start with 0 or 1");
        }
    }
}

std::string phone_number::number() const {
    return m_number;
}

std::string phone_number::area_code() const {
    return m_number.substr(static_cast<std::size_t>(0), static_cast<std::size_t>(3));
}

std::string phone_number::pretty() const {
    const std::string area = area_code();
    const std::string exchange = m_number.substr(static_cast<std::size_t>(3), static_cast<std::size_t>(3));
    const std::string subscriber = m_number.substr(static_cast<std::size_t>(6), static_cast<std::size_t>(4));
    return "(" + area + ") " + exchange + "-" + subscriber;
}

}  // namespace phone_number

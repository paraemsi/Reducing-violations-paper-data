#include "phone_number.h"
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& input) : cleaned_()
{
    std::string digits_only;
    digits_only.reserve(input.size());

    bool invalid_char_found = false;

    for (char ch : input) {
        if (is_decimal_digit(ch)) {
            digits_only.push_back(ch);
        } else if (is_permitted_separator(ch)) {
            // ignore formatting characters
        } else {
            invalid_char_found = true;
        }
    }

    const std::string::size_type ten = static_cast<std::string::size_type>(10);
    const std::string::size_type eleven = static_cast<std::string::size_type>(11);

    bool ok = (!invalid_char_found);
    std::string normalized;

    if (ok) {
        if ((digits_only.size() == eleven) && (digits_only[0] == '1')) {
            normalized = digits_only.substr(static_cast<std::string::size_type>(1));
        } else if (digits_only.size() == ten) {
            normalized = digits_only;
        } else {
            ok = false;
        }
    }

    if (ok) {
        ok = has_valid_structure(normalized);
    }

    if (!ok) {
        throw std::domain_error("invalid phone number");
    }
    cleaned_ = normalized;
}

std::string phone_number::number() const noexcept
{
    return cleaned_;
}

std::string phone_number::area_code() const noexcept
{
    return cleaned_.substr(static_cast<std::string::size_type>(0), static_cast<std::string::size_type>(3));
}

std::string phone_number::pretty() const noexcept
{
    const std::string ac = area_code();
    const std::string exchange = cleaned_.substr(static_cast<std::string::size_type>(3), static_cast<std::string::size_type>(3));
    const std::string subscriber = cleaned_.substr(static_cast<std::string::size_type>(6), static_cast<std::string::size_type>(4));
    return "(" + ac + ") " + exchange + "-" + subscriber;
}

bool phone_number::is_decimal_digit(char ch) noexcept
{
    switch (ch) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return true;
        default:
            return false;
    }
}

bool phone_number::is_permitted_separator(char ch) noexcept
{
    switch (ch) {
        case ' ':
        case '(':
        case ')':
        case '-':
        case '.':
        case '+':
            return true;
        default:
            return false;
    }
}

bool phone_number::has_valid_structure(const std::string& digits) noexcept
{
    const std::string::size_type ten = static_cast<std::string::size_type>(10);
    if (digits.size() != ten) {
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

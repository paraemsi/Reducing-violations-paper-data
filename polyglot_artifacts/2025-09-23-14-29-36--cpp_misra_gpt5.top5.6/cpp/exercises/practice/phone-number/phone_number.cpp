#include "phone_number.h"

#include <cctype>
#include <string>
#include <stdexcept>

namespace {

// Extract only decimal digits from the input string.
auto strip_to_digits(const std::string& input) -> std::string
{
    std::string digits;
    digits.reserve(input.size());

    for (char ch : input) {
        if (std::isdigit(std::char_traits<char>::to_int_type(ch)) != 0) {
            digits.push_back(ch);
        } else {
            // Non-digit; ignore
        }
    }

    return digits;
}

auto is_allowed_separator(char ch) -> bool
{
    // Allowed punctuation within NANP inputs
    const std::string allowed = "()+-. +";
    return (allowed.find(ch) != std::string::npos);
}

auto has_invalid_characters(const std::string& input) -> bool
{
    for (char ch : input) {
        if ((std::isdigit(std::char_traits<char>::to_int_type(ch)) != 0)) {
            continue;
        }
        if ((std::isalpha(std::char_traits<char>::to_int_type(ch)) != 0)) {
            return true;
        }
        if (!is_allowed_separator(ch)) {
            return true;
        }
    }
    return false;
}

}  // namespace

namespace phone_number {

phone_number::phone_number(const std::string& input)
{
    if (has_invalid_characters(input)) {
        throw std::domain_error("invalid characters");
    }

    std::string digits = strip_to_digits(input);

    if ((digits.size() == static_cast<std::size_t>(11))) {
        if (digits.front() == '1') {
            digits.erase(static_cast<std::size_t>(0), static_cast<std::size_t>(1));
        } else {
            throw std::domain_error("invalid country code");
        }
    }

    if ((digits.size() != static_cast<std::size_t>(10))) {
        throw std::domain_error("invalid number of digits");
    }

    if ((digits.at(static_cast<std::size_t>(0)) == '0') || (digits.at(static_cast<std::size_t>(0)) == '1')) {
        throw std::domain_error("invalid area code");
    }

    if ((digits.at(static_cast<std::size_t>(3)) == '0') || (digits.at(static_cast<std::size_t>(3)) == '1')) {
        throw std::domain_error("invalid exchange code");
    }

    digits_ = std::move(digits);
}

auto phone_number::number() const -> std::string
{
    return digits_;
}

auto phone_number::area_code() const -> std::string
{
    return digits_.substr(static_cast<std::size_t>(0), static_cast<std::size_t>(3));
}

auto phone_number::pretty() const -> std::string
{
    return std::string("(") + area_code() + std::string(") ")
           + digits_.substr(static_cast<std::size_t>(3), static_cast<std::size_t>(3))
           + std::string("-")
           + digits_.substr(static_cast<std::size_t>(6), static_cast<std::size_t>(4));
}

std::string clean(const std::string& input)
{
    return phone_number(input).number();
}

}  // namespace phone_number

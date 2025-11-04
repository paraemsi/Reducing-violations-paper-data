#include "phone_number.h"

#include <cctype>
#include <cstdint>
#include <stdexcept>
#include <string>

namespace phone_number {

namespace {
    // Helper to check that an area/exchange leading digit is within the allowed set [2-9]
    auto is_valid_nxx_leading_digit(const char ch) -> bool
    {
        // Equality checks on character values are permitted.
        // Avoid relational comparisons on characters to comply with the rules.
        const std::string allowed{"23456789"};
        return (allowed.find(ch) != std::string::npos);
    }
}  // namespace

std::string clean(const std::string& input)
{
    std::string digits{};
    digits.reserve(input.size());

    for (const char ch : input) {
        const std::char_traits<char>::int_type ich = std::char_traits<char>::to_int_type(ch);

        if ((std::isdigit(ich) != 0)) {
            digits.push_back(ch);
        } else if ((std::isalpha(ich) != 0)) {
            throw std::domain_error("letters not permitted in phone number");
        } else {
            // Permit only common formatting characters; everything else is invalid punctuation.
            static const std::string allowed_punct{" .-()+\t\r\n"};
            if ((allowed_punct.find(ch) != std::string::npos)) {
                // Allowed separator/formatting character: ignore.
            } else {
                throw std::domain_error("punctuations not permitted");
            }
        }
    }

    if (digits.size() == static_cast<std::size_t>(11)) {
        if ((digits.front() == '1')) {
            digits.erase(static_cast<std::size_t>(0), static_cast<std::size_t>(1));
        } else {
            throw std::domain_error("11 digits must start with country code 1");
        }
    } else if (digits.size() == static_cast<std::size_t>(10)) {
        // OK
    } else {
        throw std::domain_error("incorrect number of digits");
    }

    if ((!is_valid_nxx_leading_digit(digits[static_cast<std::size_t>(0)]))) {
        throw std::domain_error("area code cannot start with 0 or 1");
    }
    if ((!is_valid_nxx_leading_digit(digits[static_cast<std::size_t>(3)]))) {
        throw std::domain_error("exchange code cannot start with 0 or 1");
    }

    return digits;
}

phone_number::phone_number::phone_number(const std::string& input)
    : cleaned_{clean(input)}
{
}

std::string phone_number::phone_number::number() const
{
    return cleaned_;
}

std::string phone_number::phone_number::area_code() const
{
    return cleaned_.substr(static_cast<std::size_t>(0), static_cast<std::size_t>(3));
}

}  // namespace phone_number

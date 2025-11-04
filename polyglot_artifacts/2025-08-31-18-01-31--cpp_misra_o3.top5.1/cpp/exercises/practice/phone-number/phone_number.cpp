#include "phone_number.h"

#include <cstddef>
#include <string_view>
#include <stdexcept>

namespace {

/* Helper that determines if a character is one of the supplied symbols.
 * Uses only equality comparisons on the character to respect MISRA
 * “no-numeric-value-of-character” rule.
 */
[[nodiscard]] bool is_digit(char c) noexcept
{
    constexpr std::string_view valid_digits{"0123456789"};
    return (valid_digits.find(c) != std::string_view::npos);
}

[[nodiscard]] bool is_valid_leading_digit(char c) noexcept
{
    /* Leading digits of area and exchange code shall be 2-9. */
    constexpr std::string_view valid_leads{"23456789"};
    return (valid_leads.find(c) != std::string_view::npos);
}

[[nodiscard]] bool is_allowed_punctuation(char c) noexcept
{
    switch(c) {
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

} // unnamed namespace

namespace phone_number {

phone_number::phone_number(const std::string& input)
{
    std::string collected{};
    collected.reserve(input.size());

    for(char c : input) {
        if(is_digit(c)) {
            collected.push_back(c);
        } else if(is_allowed_punctuation(c)) {
            /* ignore permitted punctuation */
        } else {
            throw std::domain_error("invalid character in phone number");
        }
    }

    /* Handle optional country code and validate digit count */
    if(collected.size() == std::size_t{11U}) {
        if(collected.front() == '1') {
            collected.erase(collected.begin());
        } else {
            throw std::domain_error("11-digit number must start with country code 1");
        }
    } else if(collected.size() != std::size_t{10U}) {
        throw std::domain_error("invalid number of digits");
    }

    /* Validate leading digits of area and exchange codes */
    if(!(is_valid_leading_digit(collected[0U]))) {
        throw std::domain_error("invalid area code leading digit");
    }

    if(!(is_valid_leading_digit(collected[3U]))) {
        throw std::domain_error("invalid exchange code leading digit");
    }

    digits_ = collected;
}

std::string phone_number::number() const
{
    return digits_;
}

std::string phone_number::area_code() const
{
    return digits_.substr(0U, 3U);
}

std::string phone_number::pretty() const
{
    return '(' + digits_.substr(0U, 3U) + ") " +
           digits_.substr(3U, 3U) + '-' +
           digits_.substr(6U, 4U);
}

}  // namespace phone_number

#include "phone_number.h"

#include <cctype>
#include <cstdint>
#include <cstddef>
#include <string>
#include <stdexcept>

namespace phone_number {

namespace {
// Use cctype utilities with safe promotion via std::uint8_t -> int.
inline bool is_alpha_char(char ch) {
    return (std::isalpha(static_cast<int>(static_cast<std::uint8_t>(ch))) != 0);
}

inline bool is_digit_char(char ch) {
    return (std::isdigit(static_cast<int>(static_cast<std::uint8_t>(ch))) != 0);
}

inline bool is_invalid_nxx_lead(char ch) {
    // For NANP, 'N' is 2-9; leading digits '0' or '1' are invalid
    return ((ch == '0') || (ch == '1'));
}
}  // namespace

phone_number::phone_number(const std::string& input)
    : cleaned_number_() {
    bool has_alpha = false;
    std::string digits;
    digits.reserve(input.size());

    for (char ch : input) {
        if (is_alpha_char(ch)) {
            has_alpha = true;
        } else if (is_digit_char(ch)) {
            digits.push_back(ch);
        } else {
            // ignore punctuation, spaces, etc.
        }
    }

    if (has_alpha) {
        throw std::domain_error("invalid phone number: contains letters");
    }

    const std::size_t ten = static_cast<std::size_t>(10);
    const std::size_t eleven = static_cast<std::size_t>(11);

    if ((digits.size() == eleven) && (digits[0] == '1')) {
        digits = digits.substr(1U);
    } else if ((digits.size() == eleven) && (digits[0] != '1')) {
        throw std::domain_error("invalid phone number: bad country code");
    } else {
        // keep as-is if 10 digits; otherwise invalid
    }

    if (digits.size() != ten) {
        throw std::domain_error("invalid phone number: wrong length");
    }

    // Validate NANP constraints: area code and exchange code cannot start with 0 or 1
    if ((is_invalid_nxx_lead(digits[0])) || (is_invalid_nxx_lead(digits[3]))) {
        throw std::domain_error("invalid phone number: NXX rules violated");
    }

    cleaned_number_ = digits;
}

std::string phone_number::number() const {
    return cleaned_number_;
}

std::string phone_number::area_code() const {
    return cleaned_number_.substr(0U, 3U);
}

std::string phone_number::pretty() const {
    std::string formatted;
    formatted.reserve(static_cast<std::size_t>(14));

    formatted += '(';
    formatted += cleaned_number_.substr(0U, 3U);
    formatted += ')';
    formatted += ' ';
    formatted += cleaned_number_.substr(3U, 3U);
    formatted += '-';
    formatted += cleaned_number_.substr(6U);

    return formatted;
}

}  // namespace phone_number

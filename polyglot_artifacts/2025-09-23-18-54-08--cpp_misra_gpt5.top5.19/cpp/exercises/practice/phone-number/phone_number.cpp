#include "phone_number.h"

#include <stdexcept>
#include <string>

namespace {

// Return true if the character is one of '0'..'9' (without using relational ops on char)
inline bool is_digit_char(char ch) {
    // NOLINTNEXTLINE(readability-magic-numbers) - explicit digit list per MISRA rule
    const char* const digits = "0123456789";
    for (std::string::size_type i = 0U; digits[i] != '\0'; ++i) {
        if (ch == digits[i]) {
            return true;
        }
    }
    return false;
}

// Return true if the character is one of '2'..'9' (area/exchange leading digit)
inline bool is_n_digit_char(char ch) {
    // NOLINTNEXTLINE(readability-magic-numbers) - explicit digit list per MISRA rule
    const char* const digits = "23456789";
    for (std::string::size_type i = 0U; digits[i] != '\0'; ++i) {
        if (ch == digits[i]) {
            return true;
        }
    }
    return false;
}

inline std::string extract_digits(const std::string& input) {
    std::string out;
    out.reserve(input.size());
    for (char ch : input) {
        if (is_digit_char(ch)) {
            out.push_back(ch);
        } else {
            // ignore all non-digit characters (punctuation, spaces, '+', etc.)
        }
    }
    return out;
}

}  // namespace

namespace phone_number {

phone_number::phone_number(const std::string& input) : digits_() {
    std::string digits = extract_digits(input);

    // Handle country code '1'
    if ((digits.size() == 11U) && (digits[0] == '1')) {
        digits = digits.substr(1U);
    } else if (digits.size() == 11U) {
        throw std::domain_error("invalid country code");
    }

    if (digits.size() != 10U) {
        throw std::domain_error("invalid number of digits");
    }

    // Validate NANP rules: area code and exchange code cannot start with 0 or 1
    if (!is_n_digit_char(digits[0])) {
        throw std::domain_error("invalid area code");
    }
    if (!is_n_digit_char(digits[3])) {
        throw std::domain_error("invalid exchange code");
    }

    digits_ = digits;
}

std::string phone_number::number() const noexcept {
    return digits_;
}

std::string phone_number::area_code() const noexcept {
    return digits_.substr(0U, 3U);
}

std::string phone_number::to_string() const noexcept {
    const std::string area = digits_.substr(0U, 3U);
    const std::string exchange = digits_.substr(3U, 3U);
    const std::string subscriber = digits_.substr(6U, 4U);
    return "(" + area + ") " + exchange + "-" + subscriber;
}

}  // namespace phone_number

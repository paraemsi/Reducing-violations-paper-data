#include "phone_number.h"

#include <cctype>
#include <cstddef>
#include <stdexcept>
#include <string>

namespace phone_number {

static std::string strip_to_digits(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (char ch : s) {
        if ((std::isdigit(static_cast<unsigned char>(ch)) != 0)) {
            out.push_back(ch);
        } else {
            // ignore non-digit characters
        }
    }
    return out;
}

static bool is_invalid_n_code_char(char ch) {
    return ((ch == '0') || (ch == '1'));
}

phone_number::phone_number(const std::string& input) : digits_() {
    std::string digits = strip_to_digits(input);
    const std::size_t len = digits.size();

    if ((len == static_cast<std::size_t>(11))) {
        if ((digits[0] == '1')) {
            digits.erase(0U, 1U);
        } else {
            throw std::domain_error("Invalid country code");
        }
    } else if ((len == static_cast<std::size_t>(10))) {
        // OK
    } else {
        throw std::domain_error("Invalid number of digits");
    }

    if (is_invalid_n_code_char(digits[0])) {
        throw std::domain_error("Invalid area code");
    }
    if (is_invalid_n_code_char(digits[3])) {
        throw std::domain_error("Invalid exchange code");
    }

    digits_ = digits;
}

std::string phone_number::number() const {
    return digits_;
}

std::string phone_number::area_code() const {
    return digits_.substr(0U, 3U);
}

phone_number::operator std::string() const {
    std::string formatted;
    formatted.reserve(14U);
    formatted.push_back('(');
    formatted.append(digits_, 0U, 3U);
    formatted.push_back(')');
    formatted.push_back(' ');
    formatted.append(digits_, 3U, 3U);
    formatted.push_back('-');
    formatted.append(digits_, 6U, 4U);
    return formatted;
}

}  // namespace phone_number

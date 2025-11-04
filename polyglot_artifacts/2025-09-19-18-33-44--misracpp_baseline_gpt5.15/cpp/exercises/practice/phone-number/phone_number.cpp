#include "phone_number.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <stdexcept>

namespace phone_number {

namespace {
bool is_digit(char c) {
    return std::isdigit(static_cast<unsigned char>(c)) != 0;
}
bool is_alpha(char c) {
    return std::isalpha(static_cast<unsigned char>(c)) != 0;
}
} // namespace

phone_number::phone_number(const std::string& input) : cleaned_("0000000000") {
    std::string digits;
    bool has_alpha = false;

    for (char ch : input) {
        if (is_digit(ch)) {
            digits.push_back(ch);
        } else if (is_alpha(ch)) {
            has_alpha = true;
        } else {
            // ignore punctuation and other non-alphanumeric characters
        }
    }

    if (has_alpha) {
        throw std::domain_error("invalid phone number");
    }

    if (digits.size() == 11) {
        if (digits.front() == '1') {
            digits.erase(digits.begin()); // drop country code
        } else {
            throw std::domain_error("invalid phone number");
        }
    }

    if (digits.size() != 10) {
        throw std::domain_error("invalid phone number");
    }

    // Enforce NANP rules: NXX NXX-XXXX, where N is 2-9 and X is 0-9
    const char area_first = digits[0];
    const char exchange_first = digits[3];
    if (area_first < '2' || area_first > '9' || exchange_first < '2' || exchange_first > '9') {
        throw std::domain_error("invalid phone number");
    }

    cleaned_ = digits;
}

std::string phone_number::number() const {
    return cleaned_;
}

std::string phone_number::area_code() const {
    return cleaned_.substr(0, 3);
}

std::string phone_number::to_string() const {
    return "(" + cleaned_.substr(0, 3) + ") " + cleaned_.substr(3, 3) + "-" + cleaned_.substr(6);
}

}  // namespace phone_number

#include "phone_number.h"

#include <cctype>
#include <string>
#include <stdexcept>

namespace phone_number {

namespace {
inline bool is_alpha(char ch) {
    unsigned char uch = static_cast<unsigned char>(ch);
    return std::isalpha(uch) != 0;
}
inline bool is_digit(char ch) {
    unsigned char uch = static_cast<unsigned char>(ch);
    return std::isdigit(uch) != 0;
}
}  // namespace

phone_number::phone_number(const std::string& input) {
    std::string digits;
    digits.reserve(input.size());

    bool invalid = false;
    for (char ch : input) {
        if (is_digit(ch)) {
            digits.push_back(ch);
        } else if (is_alpha(ch)) {
            invalid = true;
        } else {
            // ignore punctuation, spaces, etc.
        }
    }

    if (!invalid) {
        if (digits.size() == 11 && digits.front() == '1') {
            digits.erase(digits.begin());
        } else if (digits.size() == 11) {
            invalid = true;
        } else if (digits.size() != 10) {
            invalid = true;
        }
    }

    if (!invalid) {
        // NANP rules: area code and exchange code cannot start with 0 or 1
        if (digits[0] == '0' || digits[0] == '1') invalid = true;
        if (digits[3] == '0' || digits[3] == '1') invalid = true;
    }

    if (invalid) {
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

std::string phone_number::pretty() const {
    return std::string("(") + area_code() + ") " + cleaned_.substr(3, 3) + "-" + cleaned_.substr(6, 4);
}

}  // namespace phone_number

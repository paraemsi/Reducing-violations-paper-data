#include "phone_number.h"

#include <cctype>
#include <string>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& input) : cleaned_() {
    std::string digits;
    digits.reserve(input.size());

    bool invalid = false;

    for (char ch : input) {
        if ((std::isdigit(static_cast<unsigned char>(ch)) != 0)) {
            digits.push_back(ch);
        } else {
            if ((std::isalpha(static_cast<unsigned char>(ch)) != 0)) {
                invalid = true;
            } else {
                if (((ch == ' ') || (ch == '(') || (ch == ')') || (ch == '.') || (ch == '-') || (ch == '+'))) {
                    // allowed formatting characters are ignored
                } else {
                    invalid = true;
                }
            }
        }
    }

    if (!invalid) {
        if ((digits.size() == static_cast<std::string::size_type>(11U))) {
            if ((digits.front() == '1')) {
                digits.erase(static_cast<std::string::size_type>(0U), static_cast<std::string::size_type>(1U));
            } else {
                invalid = true;
            }
        }
    }

    if (!invalid) {
        if ((digits.size() != static_cast<std::string::size_type>(10U))) {
            invalid = true;
        }
    }

    if (!invalid) {
        if (((digits[0] == '0') || (digits[0] == '1'))) {
            invalid = true;
        }
    }

    if (!invalid) {
        if (((digits[3] == '0') || (digits[3] == '1'))) {
            invalid = true;
        }
    }

    if (invalid) {
        throw std::domain_error("invalid phone number");
    } else {
        cleaned_ = digits;
    }
}

std::string phone_number::number() const {
    return cleaned_;
}

std::string phone_number::area_code() const {
    return cleaned_.substr(static_cast<std::string::size_type>(0U), static_cast<std::string::size_type>(3U));
}

std::string phone_number::pretty() const {
    return std::string("(") + area_code() + std::string(") ")
        + cleaned_.substr(static_cast<std::string::size_type>(3U), static_cast<std::string::size_type>(3U))
        + std::string("-")
        + cleaned_.substr(static_cast<std::string::size_type>(6U), static_cast<std::string::size_type>(4U));
}

}  // namespace phone_number

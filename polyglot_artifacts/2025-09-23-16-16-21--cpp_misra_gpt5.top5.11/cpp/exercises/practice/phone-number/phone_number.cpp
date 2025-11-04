#include "phone_number.h"

#include <cctype>
#include <string>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& input)
    : digits_() {
    std::string raw_digits;
    raw_digits.reserve(input.size());
    bool invalid{false};

    for (char ch : input) {
        if ((std::isdigit(std::char_traits<char>::to_int_type(ch)) != 0)) {
            raw_digits.push_back(ch);
        } else if (((std::isspace(std::char_traits<char>::to_int_type(ch)) != 0) ||
                    (ch == '(') || (ch == ')') || (ch == '.') ||
                    (ch == '-') || (ch == '+'))) {
            // Allowed formatting characters; ignore
        } else {
            invalid = true;
        }
    }

    if (invalid) {
        throw std::domain_error("invalid phone number");
    }

    if ((raw_digits.size() == 11U)) {
        if ((raw_digits.front() == '1')) {
            raw_digits.erase(0U, 1U);
        } else {
            throw std::domain_error("invalid phone number");
        }
    } else if ((raw_digits.size() == 10U)) {
        // OK
    } else {
        throw std::domain_error("invalid phone number");
    }

    // Enforce NANP NXX rules: area code and exchange code cannot start with '0' or '1'
    if (((raw_digits.at(0U) == '0') || (raw_digits.at(0U) == '1') ||
         (raw_digits.at(3U) == '0') || (raw_digits.at(3U) == '1'))) {
        throw std::domain_error("invalid phone number");
    }

    digits_ = raw_digits;
}

std::string phone_number::number() const {
    return digits_;
}

std::string phone_number::area_code() const {
    return digits_.substr(0U, 3U);
}

std::string phone_number::pretty() const {
    const std::string area = area_code();
    const std::string exchange = digits_.substr(3U, 3U);
    const std::string subscriber = digits_.substr(6U, 4U);
    return ("(" + area + ") " + exchange + "-" + subscriber);
}

}  // namespace phone_number

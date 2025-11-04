#include "phone_number.h"

#include <cctype>
#include <stdexcept>
#include <string>

namespace phone_number {

namespace {
bool is_allowed_non_digit(char c) {
    switch (c) {
        case ' ':
        case '(':
        case ')':
        case '-':
        case '.':
            return true;
        default:
            return false;
    }
}

bool is_valid_area_or_exchange_leading(char c) {
    return c >= '2' && c <= '9';
}
}  // namespace

phone_number::phone_number::phone_number(const std::string& input) {
    std::string raw_digits;
    raw_digits.reserve(input.size());

    for (std::size_t i = 0; i < input.size(); ++i) {
        char ch = input[i];
        unsigned char uch = static_cast<unsigned char>(ch);
        if (std::isdigit(uch)) {
            raw_digits.push_back(static_cast<char>(uch));
        } else if (ch == '+') {
            if (i != 0) {
                throw std::domain_error("invalid character in phone number");
            }
            // leading '+' is allowed and ignored
        } else if (!is_allowed_non_digit(ch)) {
            throw std::domain_error("invalid character in phone number");
        }
        // allowed punctuation is ignored
    }

    if (raw_digits.size() == 11) {
        if (raw_digits.front() != '1') {
            throw std::domain_error("11-digit number must start with country code 1");
        }
        // strip country code
        raw_digits.erase(raw_digits.begin());
    }

    if (raw_digits.size() != 10) {
        throw std::domain_error("phone number must have 10 digits");
    }

    if (!is_valid_area_or_exchange_leading(raw_digits[0])) {
        throw std::domain_error("area code must start with digits 2-9");
    }
    if (!is_valid_area_or_exchange_leading(raw_digits[3])) {
        throw std::domain_error("exchange code must start with digits 2-9");
    }

    digits_ = std::move(raw_digits);
}

std::string phone_number::phone_number::number() const {
    return digits_;
}

std::string phone_number::phone_number::area_code() const {
    return digits_.substr(0, 3);
}

std::string phone_number::phone_number::pretty() const {
    return "(" + area_code() + ") " + digits_.substr(3, 3) + "-" + digits_.substr(6, 4);
}

}  // namespace phone_number

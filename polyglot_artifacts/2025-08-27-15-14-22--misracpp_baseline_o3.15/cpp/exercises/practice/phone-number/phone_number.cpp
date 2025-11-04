#include "phone_number.h"
#include <cctype>
#include <stdexcept>

namespace phone_number {

std::string clean(const std::string& input) {
    std::string digits;
    digits.reserve(input.size());

    for (unsigned char ch : input) {
        if (std::isdigit(ch)) {
            digits.push_back(static_cast<char>(ch));
        } else if (ch == ' ' || ch == '\t' || ch == '\n' ||
                   ch == '(' || ch == ')' || ch == '-' || ch == '.' || ch == '+') {
            // allowed punctuation / whitespace, ignore
            continue;
        } else {
            throw std::domain_error("invalid character");
        }
    }

    if (digits.size() == 11) {
        if (digits.front() == '1') {
            digits.erase(digits.begin());
        } else {
            throw std::domain_error("11-digit numbers must start with 1");
        }
    }

    if (digits.size() != 10) {
        throw std::domain_error("incorrect number of digits");
    }

    // area code first digit must be 2-9
    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("invalid area code");
    }

    // exchange code first digit must be 2-9
    if (digits[3] < '2' || digits[3] > '9') {
        throw std::domain_error("invalid exchange code");
    }

    return digits;
}

phone_number::phone_number(const std::string& input)
    : digits_{clean(input)} {}

std::string phone_number::number() const {
    return digits_;
}

std::string phone_number::area_code() const {
    return digits_.substr(0, 3);
}

std::string phone_number::pretty() const {
    return "(" + digits_.substr(0, 3) + ") " +
           digits_.substr(3, 3) + "-" + digits_.substr(6);
}

}  // namespace phone_number


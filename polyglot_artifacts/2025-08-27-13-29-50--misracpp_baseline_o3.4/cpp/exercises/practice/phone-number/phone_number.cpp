#include "phone_number.h"
#include <cctype>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& input) {
    std::string raw_digits;
    raw_digits.reserve(input.size());

    for (char ch : input) {
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            raw_digits.push_back(ch);
        } else if (ch == ' ' || ch == '(' || ch == ')' || ch == '.' || ch == '-' || ch == '+') {
            // allowed formatting characters, ignore
            continue;
        } else {
            throw std::domain_error("invalid character in phone number");
        }
    }

    // Handle optional leading country code '1'
    if (raw_digits.size() == 11) {
        if (raw_digits.front() == '1') {
            raw_digits.erase(raw_digits.begin());
        } else {
            throw std::domain_error("11-digit numbers must start with country code 1");
        }
    }

    // Validate length
    if (raw_digits.size() != 10) {
        throw std::domain_error("incorrect number of digits");
    }

    // Validate area code and exchange code (cannot start with 0 or 1)
    if (raw_digits[0] < '2' || raw_digits[0] > '9' ||
        raw_digits[3] < '2' || raw_digits[3] > '9') {
        throw std::domain_error("invalid area or exchange code");
    }

    digits_ = raw_digits;
}

std::string phone_number::number() const {
    return digits_;
}

std::string phone_number::area_code() const {
    return digits_.substr(0, 3);
}

std::string phone_number::pretty() const {
    return '(' + area_code() + ") " + digits_.substr(3, 3) + '-' + digits_.substr(6);
}

}  // namespace phone_number

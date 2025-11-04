#include "phone_number.h"

#include <cctype>
#include <string>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& input) {
    std::string digits;
    digits.reserve(input.size());
    for (unsigned char ch : input) {
        if (std::isdigit(ch)) {
            digits.push_back(static_cast<char>(ch));
        } else if (std::isalpha(ch)) {
            // Letters are not allowed in phone numbers
            throw std::domain_error("invalid phone number");
        }
    }

    if (digits.size() > 11) {
        throw std::domain_error("invalid phone number");
    }

    // If there's a leading country code '1' and total is 11 digits, drop it.
    if (digits.size() == 11) {
        if (digits.front() == '1') {
            digits.erase(digits.begin());
        } else {
            throw std::domain_error("invalid phone number");
        }
    }

    // Must be exactly 10 digits now.
    if (digits.size() != 10) {
        throw std::domain_error("invalid phone number");
    }

    // Valid NANP numbers cannot start with 0 or 1 for both area code (NXX)
    // and exchange code (NXX).
    if (digits[0] < '2' || digits[0] > '9' ||
        digits[3] < '2' || digits[3] > '9') {
        throw std::domain_error("invalid phone number");
    }

    cleaned_ = std::move(digits);
}

std::string phone_number::number() const {
    return cleaned_;
}

std::string phone_number::area_code() const {
    return cleaned_.size() >= 3 ? cleaned_.substr(0, 3) : std::string();
}

std::string phone_number::pretty() const {
    if (cleaned_.size() != 10) {
        return {};
    }
    return "(" + area_code() + ") " + cleaned_.substr(3, 3) + "-" + cleaned_.substr(6, 4);
}

}  // namespace phone_number

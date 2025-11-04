#include "phone_number.h"
#include <cctype>
#include <stdexcept>
#include <string>

namespace phone_number {

phone_number::phone_number(const std::string& input) {
    std::string digits;
    digits.reserve(input.size());
    for (unsigned char ch : input) {
        if (std::isdigit(ch)) {
            digits.push_back(static_cast<char>(ch));
        } else if (std::isalpha(ch)) {
            throw std::domain_error("letters not permitted");
        }
    }

    if (digits.size() == 11) {
        if (digits.front() == '1') {
            digits.erase(digits.begin());
        } else {
            throw std::domain_error("invalid country code");
        }
    }

    if (digits.size() != 10) {
        throw std::domain_error("invalid number of digits");
    }

    // NANP rules: area code and exchange code cannot start with 0 or 1
    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("invalid area code");
    }
    if (digits[3] < '2' || digits[3] > '9') {
        throw std::domain_error("invalid exchange code");
    }

    digits_ = std::move(digits);
}

std::string phone_number::number() const {
    return digits_;
}

std::string phone_number::area_code() const {
    return digits_.substr(0, 3);
}

std::string phone_number::pretty() const {
    return "(" + area_code() + ") " + digits_.substr(3, 3) + "-" + digits_.substr(6, 4);
}

}  // namespace phone_number

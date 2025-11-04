#include "phone_number.h"
#include <cctype>
#include <stdexcept>
#include <string>

namespace phone_number {

phone_number::phone_number(const std::string& input) {
    std::string digits;
    digits.reserve(input.size());

    for (char ch : input) {
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            digits.push_back(ch);
        } else if (std::isalpha(static_cast<unsigned char>(ch))) {
            throw std::domain_error("letters not permitted");
        } else if (ch == ' ' || ch == '.' || ch == '(' || ch == ')' ||
                   ch == '-' || ch == '+') {
            // permitted separators, ignore them
        } else {
            throw std::domain_error("punctuations not permitted");
        }
    }

    if (digits.size() < 10) {
        throw std::domain_error("incorrect number of digits");
    }

    if (digits.size() == 11) {
        if (digits.front() == '1') {
            digits.erase(digits.begin());
        } else {
            throw std::domain_error("11 digits must start with 1");
        }
    }

    if (digits.size() > 11) {
        throw std::domain_error("more than 11 digits");
    }

    // By this point the number must contain exactly 10 digits
    if (digits.size() != 10) {
        throw std::domain_error("incorrect number of digits");
    }

    // Area code validations
    if (digits[0] == '0') {
        throw std::domain_error("area code cannot start with zero");
    }
    if (digits[0] == '1') {
        throw std::domain_error("area code cannot start with one");
    }

    // Exchange code validations
    if (digits[3] == '0') {
        throw std::domain_error("exchange code cannot start with zero");
    }
    if (digits[3] == '1') {
        throw std::domain_error("exchange code cannot start with one");
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
    return "(" + digits_.substr(0, 3) + ") " + digits_.substr(3, 3) +
           "-" + digits_.substr(6);
}

}  // namespace phone_number

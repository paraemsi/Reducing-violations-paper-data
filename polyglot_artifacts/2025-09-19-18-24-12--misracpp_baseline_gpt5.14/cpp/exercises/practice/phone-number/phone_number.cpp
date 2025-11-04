#include "phone_number.h"

#include <cctype>
#include <stdexcept>
#include <string>

namespace phone_number {

 

phone_number::phone_number(const std::string& input) {
    std::string digits;
    digits.reserve(input.size());
    for (unsigned char uc : input) {
        if (std::isdigit(uc)) {
            digits.push_back(static_cast<char>(uc));
        } else if (std::isalpha(uc)) {
            throw std::domain_error("letters not permitted");
        } else {
            // ignore other characters (spaces, punctuation, etc.)
        }
    }

    if (digits.size() == 11) {
        if (digits.front() == '1') {
            digits.erase(digits.begin());
        } else {
            throw std::domain_error("11 digits must start with 1");
        }
    }

    if (digits.size() != 10) {
        throw std::domain_error("incorrect number of digits");
    }

    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("area code cannot start with 0 or 1");
    }
    if (digits[3] < '2' || digits[3] > '9') {
        throw std::domain_error("exchange code cannot start with 0 or 1");
    }

    digits_ = std::move(digits);
}

std::string phone_number::number() const {
    return digits_;
}

std::string phone_number::area_code() const {
    return digits_.substr(0, 3);
}

phone_number::operator std::string() const {
    return "(" + area_code() + ") " + digits_.substr(3, 3) + "-" + digits_.substr(6);
}

}  // namespace phone_number

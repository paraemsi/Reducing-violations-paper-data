#include "phone_number.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& input) {
    std::string digits;
    digits.reserve(input.size());
    for (char ch : input) {
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            digits.push_back(ch);
        } else if (!std::isspace(static_cast<unsigned char>(ch)) &&
                   ch != '(' && ch != ')' && ch != '.' && ch != '-' && ch != '+') {
            // Presence of any alphabetic or other non-formatting character invalidates the input
            throw std::domain_error("invalid phone number");
        }
    }

    // Handle optional country code
    if (digits.size() == 11) {
        if (digits.front() == '1') {
            digits.erase(digits.begin());           // remove leading country code
        } else {
            throw std::domain_error("invalid phone number");
        }
    }

    // Length must now be exactly ten digits
    if (digits.size() != 10) {
        throw std::domain_error("invalid phone number");
    }

    // Area code and exchange code may not start with 0 or 1
    if (digits[0] < '2' || digits[0] > '9') {       // area code
        throw std::domain_error("invalid phone number");
    }
    if (digits[3] < '2' || digits[3] > '9') {       // exchange code
        throw std::domain_error("invalid phone number");
    }

    clean_ = digits;
}

std::string phone_number::number() const {
    return clean_;
}

std::string phone_number::area_code() const {
    return clean_.substr(0, 3);
}

std::string phone_number::pretty() const {
    return "(" + area_code() + ") " + clean_.substr(3, 3) + "-" + clean_.substr(6, 4);
}

}  // namespace phone_number

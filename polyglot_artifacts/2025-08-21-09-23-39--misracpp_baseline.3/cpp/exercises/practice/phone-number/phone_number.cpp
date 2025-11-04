#include "phone_number.h"

#include <cctype>
#include <stdexcept>
#include <string>
#include <algorithm>

namespace phone_number {

static std::string clean_digits(const std::string& input) {
    std::string digits;
    for (char c : input) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            digits += c;
        }
    }
    // Remove country code if present
    if (digits.length() == 11 && digits[0] == '1') {
        digits = digits.substr(1);
    }
    return digits;
}

phone_number::phone_number(std::string const& input) {
    std::string digits = clean_digits(input);

    // Validate length
    if (digits.length() != 10) {
        throw std::domain_error("Invalid number of digits");
    }

    // Validate area code and exchange code
    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("Area code must start with 2-9");
    }
    if (digits[3] < '2' || digits[3] > '9') {
        throw std::domain_error("Exchange code must start with 2-9");
    }

    number_ = digits;
}

std::string phone_number::number() const {
    return number_;
}

std::string phone_number::area_code() const {
    return number_.substr(0, 3);
}

std::string phone_number::pretty() const {
    return "(" + area_code() + ") " + number_.substr(3, 3) + "-" + number_.substr(6, 4);
}

}  // namespace phone_number

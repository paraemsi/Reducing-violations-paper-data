#include "phone_number.h"

#include <string>
#include <cctype>
#include <stdexcept>
#include <sstream>

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

phone_number::phone_number(const std::string& input) {
    digits_ = clean_digits(input);

    // Validate length
    if (digits_.length() != 10) {
        throw std::domain_error("Invalid number of digits");
    }

    // Validate area code and exchange code
    if (digits_[0] < '2' || digits_[0] > '9') {
        throw std::domain_error("Area code must start with 2-9");
    }
    if (digits_[3] < '2' || digits_[3] > '9') {
        throw std::domain_error("Exchange code must start with 2-9");
    }
}

std::string phone_number::number() const {
    return digits_;
}

std::string phone_number::area_code() const {
    return digits_.substr(0, 3);
}

std::string phone_number::pretty() const {
    std::ostringstream oss;
    oss << "(" << digits_.substr(0, 3) << ") "
        << digits_.substr(3, 3) << "-"
        << digits_.substr(6, 4);
    return oss.str();
}

}  // namespace phone_number

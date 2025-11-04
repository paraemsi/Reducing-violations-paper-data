#include "phone_number.h"

#include <cctype>
#include <stdexcept>
#include <string>
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
    cleaned_ = clean_digits(input);

    // Validate length
    if (cleaned_.length() != 10) {
        throw std::domain_error("Invalid phone number length");
    }
    // Area code and exchange code must start with 2-9
    if (cleaned_[0] < '2' || cleaned_[0] > '9') {
        throw std::domain_error("Invalid area code");
    }
    if (cleaned_[3] < '2' || cleaned_[3] > '9') {
        throw std::domain_error("Invalid exchange code");
    }
}

std::string phone_number::number() const {
    return cleaned_;
}

std::string phone_number::area_code() const {
    return cleaned_.substr(0, 3);
}

std::string phone_number::pretty() const {
    std::ostringstream oss;
    oss << "(" << cleaned_.substr(0, 3) << ") "
        << cleaned_.substr(3, 3) << "-"
        << cleaned_.substr(6, 4);
    return oss.str();
}

} // namespace phone_number

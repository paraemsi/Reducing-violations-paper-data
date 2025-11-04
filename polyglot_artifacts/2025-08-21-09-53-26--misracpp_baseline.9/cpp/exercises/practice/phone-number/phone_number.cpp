#include "phone_number.h"

#include <string>
#include <cctype>
#include <stdexcept>
#include <sstream>

namespace phone_number {

static std::string clean(const std::string& input) {
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
    // Validation
    if (digits.length() != 10)
        throw std::domain_error("Invalid number of digits");

    // Area code and exchange code must start with 2-9
    if (digits[0] < '2' || digits[0] > '9')
        throw std::domain_error("Invalid area code");
    if (digits[3] < '2' || digits[3] > '9')
        throw std::domain_error("Invalid exchange code");

    return digits;
}

phone_number::phone_number(const std::string& input)
    : cleaned_(clean(input))
{}

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

}  // namespace phone_number

#include "phone_number.h"

#include <cctype>
#include <stdexcept>
#include <string>
#include <sstream>

namespace phone_number {

static std::string only_digits(const std::string& input) {
    std::string digits;
    for (char c : input) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            digits += c;
        }
    }
    return digits;
}

static bool valid_area_code(const std::string& digits) {
    return digits.size() >= 1 && digits[0] >= '2' && digits[0] <= '9';
}

static bool valid_exchange_code(const std::string& digits) {
    return digits.size() >= 4 && digits[3] >= '2' && digits[3] <= '9';
}

std::string clean(const std::string& input) {
    std::string digits = only_digits(input);

    if (digits.length() == 11 && digits[0] == '1') {
        digits = digits.substr(1);
    }

    if (digits.length() != 10) {
        throw std::domain_error("invalid number of digits");
    }
    if (!valid_area_code(digits)) {
        throw std::domain_error("invalid area code");
    }
    if (!valid_exchange_code(digits)) {
        throw std::domain_error("invalid exchange code");
    }

    return digits;
}

phone_number::phone_number(const std::string& input) {
    number_ = clean(input);
}

std::string phone_number::number() const {
    return number_;
}

std::string phone_number::area_code() const {
    return number_.substr(0, 3);
}

std::string phone_number::pretty() const {
    std::ostringstream oss;
    oss << "(" << area_code() << ") " << number_.substr(3, 3) << "-" << number_.substr(6, 4);
    return oss.str();
}

}  // namespace phone_number

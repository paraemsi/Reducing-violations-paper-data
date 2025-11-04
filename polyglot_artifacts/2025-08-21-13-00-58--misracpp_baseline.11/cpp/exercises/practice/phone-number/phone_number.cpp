#include "phone_number.h"

#include <cctype>
#include <stdexcept>
#include <string>

namespace phone_number {

static bool is_valid_area_code(const std::string& digits) {
    // Area code: NXX, N=2-9, X=0-9
    return digits.size() >= 1 && digits[0] >= '2' && digits[0] <= '9';
}

static bool is_valid_exchange_code(const std::string& digits) {
    // Exchange code: NXX, N=2-9, X=0-9
    return digits.size() >= 4 && digits[3] >= '2' && digits[3] <= '9';
}

phone_number::phone_number(const std::string& input) {
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

    if (digits.length() != 10) {
        throw std::domain_error("Phone number must be 10 digits");
    }

    // Area code and exchange code validation
    if (!(is_valid_area_code(digits) && is_valid_exchange_code(digits))) {
        throw std::domain_error("Invalid area or exchange code");
    }

    cleaned_number_ = digits;
}

std::string phone_number::number() const {
    return cleaned_number_;
}

} // namespace phone_number

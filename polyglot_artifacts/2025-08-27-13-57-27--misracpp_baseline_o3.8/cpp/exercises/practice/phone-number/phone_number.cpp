#include "phone_number.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <stdexcept>

namespace phone_number {

// helper: true if the 10-digit NANP rules are met
bool phone_number::valid(const std::string& digits) {
    if (digits.size() != 10) return false;
    // Area code and exchange code cannot start with 0 or 1
    return (digits[0] >= '2' && digits[0] <= '9') &&
           (digits[3] >= '2' && digits[3] <= '9');
}

phone_number::phone_number(const std::string& raw) {
    // Keep only digit characters from the input
    std::string digits;
    digits.reserve(raw.size());
    for (char ch : raw) {
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            digits.push_back(ch);
        }
    }

    // Handle optional country code
    if (digits.size() == 11) {
        if (digits.front() != '1') {
            throw std::domain_error("11-digit numbers must start with country code 1");
        }
        digits.erase(digits.begin());  // drop leading country code
    }

    // Must be exactly 10 digits after possible country-code removal
    if (digits.size() != 10 || !valid(digits)) {
        throw std::domain_error("invalid NANP phone number");
    }

    digits_ = digits;
}

std::string phone_number::number() const {
    return digits_;
}

std::string phone_number::area_code() const {
    return digits_.substr(0, 3);
}

std::string phone_number::pretty() const {
    return "(" + area_code() + ") "
           + digits_.substr(3, 3) + "-"
           + digits_.substr(6, 4);
}

}  // namespace phone_number

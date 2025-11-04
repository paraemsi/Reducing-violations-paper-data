#include "phone_number.h"

#include <cctype>
#include <utility>  // for std::move
#include <stdexcept>

namespace phone_number {

namespace {

bool is_valid_nanp(const std::string& digits) {
    return digits.size() == 10 &&
           digits[0] >= '2' && digits[0] <= '9' &&         // area code first digit
           digits[3] >= '2' && digits[3] <= '9';           // exchange code first digit
}
}  // namespace

phone_number::phone_number(const std::string& input) {
    std::string digits;
    digits.reserve(input.size());

    // Extract numeric characters only
    for (char ch : input) {
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            digits.push_back(ch);
        }
    }

    // Handle country code and basic length validation
    if (digits.size() == 11) {
        if (digits.front() != '1') {
            throw std::domain_error("11-digit numbers must start with country code 1");
        }
        digits.erase(digits.begin());  // remove country code
    }

    if (digits.size() != 10) {
        throw std::domain_error("Phone number must contain exactly 10 digits");
    }

    // NANP-specific validation
    if (!is_valid_nanp(digits)) {
        throw std::domain_error("Invalid NANP phone number");
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
    return "(" + area_code() + ") " + digits_.substr(3, 3) + "-" + digits_.substr(6, 4);
}

}  // namespace phone_number

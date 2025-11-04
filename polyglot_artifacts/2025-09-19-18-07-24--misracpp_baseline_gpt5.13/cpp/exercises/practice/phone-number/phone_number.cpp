#include "phone_number.h"

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
        }
    }

    if (digits.size() == 11 && digits.front() == '1') {
        digits.erase(digits.begin());
    }

    if (!is_valid(digits)) {
        throw std::domain_error("invalid phone number");
    } else {
        digits_ = digits;
    }
}

std::string phone_number::number() const {
    return digits_;
}

std::string phone_number::area_code() const {
    return digits_.substr(0, 3);
}

std::string phone_number::pretty() const {
    return "(" + area_code() + ") " + digits_.substr(3, 3) + "-" + digits_.substr(6);
}

bool phone_number::is_valid(const std::string& digits) {
    if (digits.size() != 10) return false;
    if (digits[0] < '2' || digits[0] > '9') return false;
    if (digits[3] < '2' || digits[3] > '9') return false;
    return true;
}

}  // namespace phone_number

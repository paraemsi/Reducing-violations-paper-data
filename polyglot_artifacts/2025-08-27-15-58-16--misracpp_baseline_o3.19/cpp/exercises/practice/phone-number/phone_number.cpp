#include "phone_number.h"
#include <cctype>
#include <string>
#include <stdexcept>

namespace phone_number {

// Helper: strip everything that is not a digit
namespace {
std::string only_digits(const std::string &input) {
    std::string out;
    out.reserve(input.size());
    for (char ch : input) {
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            out.push_back(ch);
        }
    }
    return out;
}
} // unnamed namespace

bool phone_number::phone_number::is_valid(const std::string &digits) {
    if (digits.size() != 10) {
        return false;
    }
    // Area code first digit must be 2-9
    if (digits[0] < '2') {
        return false;
    }
    // Exchange code first digit must be 2-9
    if (digits[3] < '2') {
        return false;
    }
    return true;
}

phone_number::phone_number::phone_number(const std::string &input) {
    std::string digits = only_digits(input);

    // Handle optional country code
    if (digits.size() == 11) {
        if (digits.front() == '1') {
            digits.erase(digits.begin());  // remove leading country code
        } else {
            throw std::domain_error("invalid phone number");
        }
    }

    // Validate after optional country code removal
    if (!is_valid(digits)) {
        throw std::domain_error("invalid phone number");
    }

    digits_ = digits;
}

std::string phone_number::phone_number::number() const {
    return digits_;
}

std::string phone_number::phone_number::area_code() const {
    return digits_.substr(0, 3);
}

std::string phone_number::phone_number::pretty() const {
    return "(" + area_code() + ") " + digits_.substr(3, 3) + "-" +
           digits_.substr(6, 4);
}

}  // namespace phone_number

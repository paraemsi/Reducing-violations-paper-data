#include "phone_number.h"
#include <cctype>
#include <stdexcept>

namespace phone_number {

namespace {


bool valid_area_code(const std::string& digits) {
    return digits[0] >= '2' && digits[0] <= '9';
}

bool valid_exchange_code(const std::string& digits) {
    return digits[3] >= '2' && digits[3] <= '9';
}

std::string clean_digits(const std::string& input) {
    std::string digits;
    digits.reserve(input.size());
    for (char ch : input) {
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            digits.push_back(ch);
        }
    }

    if (digits.size() == 11 && digits[0] == '1') {
        digits.erase(0, 1); // remove leading country code
    }

    if (digits.size() != 10 || !valid_area_code(digits) || !valid_exchange_code(digits)) {
        throw std::domain_error{"invalid phone number"};
    }

    return digits;
}

}  // namespace

// ---- phone_number class implementation ----

phone_number::phone_number::phone_number(const std::string& input)
    : digits_{clean_digits(input)} {}

std::string phone_number::phone_number::number() const {
    return digits_;
}

std::string phone_number::phone_number::area_code() const {
    return digits_.substr(0, 3);
}

std::string phone_number::phone_number::pretty() const {
    return "(" + digits_.substr(0, 3) + ") " + digits_.substr(3, 3) + "-" + digits_.substr(6, 4);
}

}  // namespace phone_number

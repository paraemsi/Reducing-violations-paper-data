#include "phone_number.h"
#include <algorithm>
#include <cctype>
#include <string>
#include <stdexcept>

namespace phone_number {

namespace {

std::string only_digits(const std::string &input) {
    std::string result;
    for (char c : input) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            result.push_back(c);
        }
    }
    return result;
}

std::string strip_country_code(const std::string &digits) {
    if (digits.size() == 11 && digits[0] == '1') {
        return digits.substr(1);
    }
    return digits;
}

bool is_valid(const std::string &digits) {
    if (digits.size() != 10) return false;

    // Area code and exchange code cannot start with 0 or 1
    if (digits[0] == '0' || digits[0] == '1') return false;
    if (digits[3] == '0' || digits[3] == '1') return false;

    return true;
}


} // namespace


phone_number::phone_number(const std::string &input)
    : digits_{clean_number(input)} {}

std::string phone_number::clean_number(const std::string &input) {
    std::string digits = only_digits(input);
    digits = strip_country_code(digits);

    if (!is_valid(digits)) {
        throw std::domain_error("invalid phone number");
    }
    return digits;
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

}  // namespace phone_number

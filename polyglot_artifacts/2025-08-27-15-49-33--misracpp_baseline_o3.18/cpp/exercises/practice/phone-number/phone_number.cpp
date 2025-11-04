#include "phone_number.h"
#include <cctype>
#include <stdexcept>

namespace phone_number {

namespace {

// helper: strip all non-digit characters
std::string only_digits(const std::string& str) {
    std::string out;
    out.reserve(str.size());
    for (unsigned char c : str) {
        if (std::isdigit(c)) {
            out.push_back(static_cast<char>(c));
        }
    }
    return out;
}

// helper: true if digit is between '2' and '9'
bool valid_leading(char c) {
    return c >= '2' && c <= '9';
}

} // namespace

phone_number::phone_number(const std::string& input) {
    std::string digits = only_digits(input);

    // strip leading country code '1' if present
    if (digits.size() == 11 && digits.front() == '1') {
        digits.erase(digits.begin());
    }

    // Validate size and leading digits of area & exchange codes
    if (digits.size() != 10 || !valid_leading(digits[0]) || !valid_leading(digits[3])) {
        throw std::domain_error("invalid phone number");
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
    return "(" + area_code() + ") " +
           digits_.substr(3, 3) + "-" +
           digits_.substr(6, 4);
}

}  // namespace phone_number

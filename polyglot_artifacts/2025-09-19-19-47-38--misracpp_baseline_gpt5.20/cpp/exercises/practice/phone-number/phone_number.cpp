#include "phone_number.h"

#include <cctype>
#include <string>
#include <stdexcept>

namespace {

// Return true if input contains any alphabetic characters.
bool contains_alpha(const std::string& s) {
    for (unsigned char ch : s) {
        if (std::isalpha(ch)) return true;
    }
    return false;
}

// Keep only digit characters.
std::string extract_digits(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (unsigned char ch : s) {
        if (std::isdigit(ch)) out.push_back(static_cast<char>(ch));
    }
    return out;
}

bool valid_area_and_exchange(const std::string& digits10) {
    // Assumes size >= 4
    return (digits10[0] >= '2' && digits10[0] <= '9') &&
           (digits10[3] >= '2' && digits10[3] <= '9');
}


std::string clean_number(const std::string& input) {
    if (contains_alpha(input)) {
        throw std::domain_error("invalid number");
    }

    std::string digits = extract_digits(input);

    if (digits.size() == 11) {
        if (digits.front() != '1') throw std::domain_error("invalid number");
        digits.erase(digits.begin());  // remove leading country code '1'
    } else if (digits.size() != 10) {
        throw std::domain_error("invalid number");
    }

    if (!valid_area_and_exchange(digits)) {
        throw std::domain_error("invalid number");
    }

    return digits;
}

}  // namespace

namespace phone_number {

phone_number::phone_number(const std::string& input)
    : digits_{clean_number(input)} {}

std::string phone_number::number() const {
    return digits_;
}

std::string phone_number::area_code() const {
    return digits_.substr(0, 3);
}

std::string phone_number::pretty() const {
    return "(" + digits_.substr(0, 3) + ") " + digits_.substr(3, 3) + "-" + digits_.substr(6, 4);
}

}  // namespace phone_number

#include "phone_number.h"
#include <string>
#include <stdexcept>
#include <cctype>
#include <algorithm>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // First, extract all digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(c)) {
            digits.push_back(c);
        }
    }
    
    // Check number of digits
    if (digits.size() == 11) {
        if (digits[0] != '1') {
            throw std::domain_error("11 digits must start with 1");
        }
        // Remove the country code
        digits = digits.substr(1);
    } else if (digits.size() != 10) {
        if (digits.size() < 10) {
            throw std::domain_error("incorrect number of digits");
        } else {
            throw std::domain_error("more than 11 digits");
        }
    }
    
    // Check area code (first digit N from 2-9)
    if (digits[0] == '0' || digits[0] == '1') {
        throw std::domain_error("area code cannot start with zero or one");
    }
    
    // Check exchange code (fourth digit N from 2-9)
    if (digits[3] == '0' || digits[3] == '1') {
        throw std::domain_error("exchange code cannot start with zero or one");
    }
    
    number_ = digits;
}

std::string phone_number::number() const {
    return number_;
}

std::string phone_number::area_code() const {
    return number_.substr(0, 3);
}

phone_number::operator std::string() const {
    // Format as NXX NXX-XXXX
    return "(" + area_code() + ") " + number_.substr(3, 3) + "-" + number_.substr(6);
}

}  // namespace phone_number

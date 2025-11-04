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
            digits += c;
        }
    }
    
    // Check if the number has a country code
    if (digits.size() == 11) {
        if (digits[0] == '1') {
            // Remove the country code
            digits = digits.substr(1);
        } else {
            throw std::domain_error("Invalid number");
        }
    }
    
    // Check if the number is exactly 10 digits
    if (digits.size() != 10) {
        throw std::domain_error("Invalid number");
    }
    
    // Validate area code (first digit between 2-9)
    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("Invalid number");
    }
    
    // Validate exchange code (fourth digit between 2-9)
    if (digits[3] < '2' || digits[3] > '9') {
        throw std::domain_error("Invalid number");
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
    return "(" + area_code() + ") " + number_.substr(3, 3) + "-" + number_.substr(6);
}

}  // namespace phone_number

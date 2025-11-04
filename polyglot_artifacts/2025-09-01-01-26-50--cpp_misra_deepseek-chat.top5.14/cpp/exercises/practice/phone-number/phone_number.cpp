#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // Extract only digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            digits.push_back(c);
        }
    }
    
    // Check length and handle country code
    if (digits.length() == 11) {
        if (digits[0] == '1') {
            // Remove the country code
            digits = digits.substr(1);
        } else {
            throw std::domain_error("Invalid country code");
        }
    }
    
    // Check if the number is exactly 10 digits
    if (digits.length() != 10) {
        throw std::domain_error("Invalid number of digits");
    }
    
    // Check area code (first digit)
    if ((digits[0] < '2') || (digits[0] > '9')) {
        throw std::domain_error("Area code cannot start with 0 or 1");
    }
    
    // Check exchange code (fourth digit)
    if ((digits[3] < '2') || (digits[3] > '9')) {
        throw std::domain_error("Exchange code cannot start with 0 or 1");
    }
    
    number_ = digits;
}

std::string phone_number::number() const {
    return number_;
}

std::string phone_number::area_code() const {
    return number_.substr(0, 3);
}

}  // namespace phone_number

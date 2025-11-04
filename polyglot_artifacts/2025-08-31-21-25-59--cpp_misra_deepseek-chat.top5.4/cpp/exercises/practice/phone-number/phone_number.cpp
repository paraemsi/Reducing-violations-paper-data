#include "phone_number.h"
#include <string>
#include <stdexcept>
#include <cctype>

namespace phone_number {

phone_number::phone_number(const std::string& number) {
    // Extract digits
    std::string digits;
    for (char c : number) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            digits.push_back(c);
        }
    }
    
    // Check number length
    if (digits.length() == 11) {
        if (digits[0] != '1') {
            throw std::domain_error("Invalid country code");
        }
        // Remove country code
        digits = digits.substr(1);
    } else if (digits.length() != 10) {
        throw std::domain_error("Invalid number of digits");
    }
    
    // Now we have exactly 10 digits
    // Validate area code (NXX) - first digit must be 2-9
    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("Area code cannot start with zero or one");
    }
    
    // Validate exchange code (NXX) - first digit must be 2-9
    if (digits[3] < '2' || digits[3] > '9') {
        throw std::domain_error("Exchange code cannot start with zero or one");
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

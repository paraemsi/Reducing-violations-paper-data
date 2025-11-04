#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // Extract all digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            digits.push_back(c);
        }
    }
    
    // Check length and handle country code
    if (digits.length() == 11) {
        if (digits[0] == '1') {
            digits = digits.substr(1);
        } else {
            throw std::domain_error("Invalid country code");
        }
    }
    
    // Validate length
    if (digits.length() != 10) {
        throw std::domain_error("Invalid number of digits");
    }
    
    // Validate area code (first digit)
    if (digits[0] == '0' || digits[0] == '1') {
        throw std::domain_error("Area code cannot start with zero or one");
    }
    
    // Validate exchange code (fourth digit)
    if (digits[3] == '0' || digits[3] == '1') {
        throw std::domain_error("Exchange code cannot start with zero or one");
    }
    
    cleaned_number = digits;
}

std::string phone_number::number() const {
    return cleaned_number;
}

std::string phone_number::area_code() const {
    return cleaned_number.substr(0, 3);
}

phone_number::operator std::string() const {
    return "(" + area_code() + ") " + cleaned_number.substr(3, 3) + "-" + cleaned_number.substr(6);
}

}  // namespace phone_number

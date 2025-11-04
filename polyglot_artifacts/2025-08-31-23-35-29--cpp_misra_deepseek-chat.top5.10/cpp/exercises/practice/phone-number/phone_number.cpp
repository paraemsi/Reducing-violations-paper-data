#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>
#include <cstdint>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // Extract all digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            digits.push_back(c);
        }
    }
    
    // Check length
    if (digits.length() == 11U) {
        // Check if the first digit is the country code '1'
        if (digits[0] == '1') {
            // Remove the country code
            digits = digits.substr(1);
        } else {
            throw std::domain_error("Invalid number of digits");
        }
    }
    
    // After processing, the number must be exactly 10 digits
    if (digits.length() != 10U) {
        throw std::domain_error("Invalid number of digits");
    }
    
    // Check area code (first digit)
    if ((digits[0] == '0') || (digits[0] == '1')) {
        throw std::domain_error("Area code cannot start with zero or one");
    }
    
    // Check exchange code (fourth digit)
    if ((digits[3] == '0') || (digits[3] == '1')) {
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

#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>
#include <cstdint>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // First, extract all digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            digits.push_back(c);
        }
    }
    
    // Check length
    if (digits.length() == 11) {
        if (digits[0] != '1') {
            throw std::domain_error("Invalid country code");
        }
        // Remove the country code
        digits = digits.substr(1);
    } else {
        if (digits.length() != 10) {
            throw std::domain_error("Invalid number of digits");
        }
    }
    
    // Check area code (first digit must be between '2' and '9')
    // Use allowed equality comparisons only
    const std::string valid_first_digits = "23456789";
    if (valid_first_digits.find(digits[0]) == std::string::npos) {
        throw std::domain_error("Area code cannot start with zero or one");
    }
    
    // Check exchange code (fourth digit must be between '2' and '9')
    if (valid_first_digits.find(digits[3]) == std::string::npos) {
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
    // Format as NXX NXX-XXXX
    return "(" + area_code() + ") " + cleaned_number.substr(3, 3) + "-" + cleaned_number.substr(6);
}

}  // namespace phone_number

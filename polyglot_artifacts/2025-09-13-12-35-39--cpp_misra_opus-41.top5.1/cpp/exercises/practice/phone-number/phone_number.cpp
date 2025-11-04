#include "phone_number.h"
#include <cstdint>
#include <cctype>
#include <stdexcept>

namespace phone_number {

PhoneNumber::PhoneNumber(const std::string& input) {
    // Extract only digits from the input
    std::string digits;
    for (std::size_t i = 0; i < input.length(); ++i) {
        if (std::isdigit(input[i])) {
            digits += input[i];
        }
    }
    
    // Check if we have 10 or 11 digits
    if (digits.length() == 11) {
        // If 11 digits, first must be '1' (country code)
        if (digits[0] != '1') {
            throw std::domain_error("11 digits must start with 1");
        }
        // Remove the country code
        digits = digits.substr(1);
    }
    
    // Now we should have exactly 10 digits
    if (digits.length() != 10) {
        if (digits.length() < 10) {
            throw std::domain_error("not enough digits");
        } else {
            throw std::domain_error("more than 11 digits");
        }
    }
    
    // Validate area code (first digit must be 2-9)
    if ((digits[0] < '2') || (digits[0] > '9')) {
        if (digits[0] == '0') {
            throw std::domain_error("area code cannot start with zero");
        } else if (digits[0] == '1') {
            throw std::domain_error("area code cannot start with one");
        } else {
            throw std::domain_error("invalid area code");
        }
    }
    
    // Validate exchange code (fourth digit must be 2-9)
    if ((digits[3] < '2') || (digits[3] > '9')) {
        if (digits[3] == '0') {
            throw std::domain_error("exchange code cannot start with zero");
        } else if (digits[3] == '1') {
            throw std::domain_error("exchange code cannot start with one");
        } else {
            throw std::domain_error("invalid exchange code");
        }
    }
    
    cleaned_number = digits;
}

std::string PhoneNumber::number() const {
    return cleaned_number;
}

}  // namespace phone_number

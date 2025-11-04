#include "phone_number.h"
#include <algorithm>
#include <cctype>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& phone_number_string) {
    cleaned_number = clean_and_validate(phone_number_string);
}

std::string phone_number::number() const {
    return cleaned_number;
}

std::string phone_number::clean_and_validate(const std::string& input) const {
    // Extract only digits from the input
    std::string digits;
    for (char c : input) {
        if (std::isdigit(c)) {
            digits += c;
        }
    }
    
    // Check if it's 11 digits with country code 1
    if (digits.length() == 11) {
        if (digits[0] != '1') {
            throw std::domain_error("Invalid country code");
        }
        // Remove the country code
        digits = digits.substr(1);
    }
    
    // Must be exactly 10 digits at this point
    if (digits.length() != 10) {
        throw std::domain_error("Invalid phone number length");
    }
    
    // Validate area code (first digit must be 2-9)
    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("Invalid area code");
    }
    
    // Validate exchange code (fourth digit must be 2-9)
    if (digits[3] < '2' || digits[3] > '9') {
        throw std::domain_error("Invalid exchange code");
    }
    
    return digits;
}

}  // namespace phone_number

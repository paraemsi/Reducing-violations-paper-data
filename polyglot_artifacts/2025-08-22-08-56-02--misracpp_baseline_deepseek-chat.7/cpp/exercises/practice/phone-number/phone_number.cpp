#include "phone_number.h"
#include <string>
#include <stdexcept>
#include <cctype>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // Extract all digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(c)) {
            digits.push_back(c);
        }
    }
    
    // Validate the number of digits
    if (digits.size() == 11) {
        // Check if the first digit is the country code '1'
        if (digits[0] != '1') {
            throw std::domain_error("invalid number");
        }
        // Remove the country code
        digits = digits.substr(1);
    } else if (digits.size() != 10) {
        throw std::domain_error("invalid number");
    }
    
    // Now we should have exactly 10 digits
    // Validate area code (first digit of first 3 digits)
    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("invalid number");
    }
    // Validate exchange code (first digit of next 3 digits)
    if (digits[3] < '2' || digits[3] > '9') {
        throw std::domain_error("invalid number");
    }
    
    cleaned_number = digits;
}

std::string phone_number::number() const {
    return cleaned_number;
}

std::string phone_number::area_code() const {
    return cleaned_number.substr(0, 3);
}

}  // namespace phone_number

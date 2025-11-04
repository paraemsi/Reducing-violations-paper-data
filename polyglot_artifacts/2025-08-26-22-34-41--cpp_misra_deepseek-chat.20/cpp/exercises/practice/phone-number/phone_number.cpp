#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // First, extract all digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(c)) {
            digits.push_back(c);
        }
    }
    
    // Check length
    if (digits.length() < 10) {
        throw std::domain_error("must not be fewer than 10 digits");
    }
    if (digits.length() > 11) {
        throw std::domain_error("must not be greater than 11 digits");
    }
    
    // Handle country code
    if (digits.length() == 11) {
        if (digits[0] != '1') {
            throw std::domain_error("11 digits must start with 1");
        }
        // Remove the country code
        digits = digits.substr(1);
    }
    // Now digits should be exactly 10 characters long
    
    // Check area code (first digit)
    if (digits[0] == '0' || digits[0] == '1') {
        throw std::domain_error("area code cannot start with zero or one");
    }
    
    // Check exchange code (fourth digit)
    if (digits[3] == '0' || digits[3] == '1') {
        throw std::domain_error("exchange code cannot start with zero or one");
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

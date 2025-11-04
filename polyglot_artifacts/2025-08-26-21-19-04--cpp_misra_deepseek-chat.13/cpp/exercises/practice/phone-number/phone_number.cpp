#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>
#include <algorithm>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // Extract only the digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(c)) {
            digits.push_back(c);
        }
    }
    
    // Check number of digits
    if (digits.length() == 11) {
        // Check if the country code is valid (must be '1')
        if (digits[0] != '1') {
            throw std::domain_error("Invalid country code");
        }
        // Remove the country code to get the 10-digit number
        digits = digits.substr(1);
    } 
    // Check if we have exactly 10 digits
    if (digits.length() != 10) {
        throw std::domain_error("Invalid number of digits");
    }
    
    // Validate area code (first 3 digits) - first digit must be between 2-9
    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("Area code cannot start with 0 or 1");
    }
    
    // Validate exchange code (fourth digit) must be between 2-9
    if (digits[3] < '2' || digits[3] > '9') {
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

phone_number::operator std::string() const {
    // Format the number as (NXX) NXX-XXXX
    return "(" + area_code() + ") " + number_.substr(3, 3) + "-" + number_.substr(6);
}

}  // namespace phone_number

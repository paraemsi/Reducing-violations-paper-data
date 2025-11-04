#include "phone_number.h"
#include <string>
#include <stdexcept>
#include <cctype>
#include <algorithm>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // Extract all digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(c)) {
            digits.push_back(c);
        }
    }
    
    // Check length
    if (digits.size() == 11) {
        if (digits[0] != '1') {
            throw std::domain_error("Invalid country code");
        }
        // Remove the leading '1'
        digits.erase(0, 1);
    }
    
    // After processing, the number must be exactly 10 digits
    if (digits.size() != 10) {
        throw std::domain_error("Invalid number of digits");
    }
    
    // Check area code (NXX) - first digit
    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("Area code cannot start with zero or one");
    }
    
    // Check exchange code (NXX) - fourth digit
    if (digits[3] < '2' || digits[3] > '9') {
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

}  // namespace phone_number

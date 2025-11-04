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
    
    // Check number length
    if (digits.size() == 11) {
        // Check if the first digit is the country code '1'
        if (digits[0] != '1') {
            throw std::domain_error("Invalid number");
        }
        // Remove country code
        digits.erase(0, 1);
    }
    
    // After processing, we should have exactly 10 digits
    if (digits.size() != 10) {
        throw std::domain_error("Invalid number");
    }
    
    // Check area code (NXX) - first digit must be between 2-9
    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("Invalid number");
    }
    
    // Check exchange code (NXX) - fourth digit must be between 2-9
    if (digits[3] < '2' || digits[3] > '9') {
        throw std::domain_error("Invalid number");
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

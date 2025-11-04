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
        if (digits[0] == '1') {
            digits = digits.substr(1);
        } else {
            throw std::domain_error("Invalid number");
        }
    } else if (digits.size() != 10) {
        throw std::domain_error("Invalid number");
    }
    
    // Now we should have exactly 10 digits
    // Validate area code (NXX)
    if (digits[0] == '0' || digits[0] == '1') {
        throw std::domain_error("Invalid area code");
    }
    // Validate exchange code (NXX)
    if (digits[3] == '0' || digits[3] == '1') {
        throw std::domain_error("Invalid exchange code");
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

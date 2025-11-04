#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>
#include <algorithm>

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
    if (digits.length() == 11) {
        // Check if the first digit is the country code '1'
        if (digits[0] != '1') {
            throw std::domain_error("Invalid country code");
        }
        // Remove country code
        digits.erase(0, 1);
    }
    
    // Check if we now have exactly 10 digits
    if (digits.length() != 10) {
        throw std::domain_error("Invalid number of digits");
    }
    
    // Check area code (first digit of first 3 digits)
    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("Area code cannot start with 0 or 1");
    }
    
    // Check exchange code (first digit of next 3 digits)
    if (digits[3] < '2' || digits[3] > '9') {
        throw std::domain_error("Exchange code cannot start with 0 or 1");
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
    // Format as (NXX) NXX-XXXX
    return "(" + area_code() + ") " + cleaned_number.substr(3, 3) + "-" + cleaned_number.substr(6);
}

}  // namespace phone_number

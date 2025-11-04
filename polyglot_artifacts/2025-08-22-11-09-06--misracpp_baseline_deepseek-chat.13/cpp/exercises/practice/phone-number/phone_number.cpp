#include "phone_number.h"
#include <string>
#include <stdexcept>
#include <cctype>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // Extract all digits
    for (char c : raw_number) {
        if (std::isdigit(c)) {
            cleaned_number += c;
        }
    }
    
    // Check length and handle country code
    if (cleaned_number.length() == 11) {
        if (cleaned_number[0] != '1') {
            throw std::domain_error("Invalid country code");
        }
        // Remove the '1' prefix
        cleaned_number = cleaned_number.substr(1);
    }
    
    // Check if the number now has exactly 10 digits
    if (cleaned_number.length() != 10) {
        throw std::domain_error("Invalid number of digits");
    }
    
    // Check area code (first digit)
    if (cleaned_number[0] == '0' || cleaned_number[0] == '1') {
        throw std::domain_error("Area code cannot start with zero or one");
    }
    
    // Check exchange code (fourth digit)
    if (cleaned_number[3] == '0' || cleaned_number[3] == '1') {
        throw std::domain_error("Exchange code cannot start with zero or one");
    }
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

#include "phone_number.h"
#include <string>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include <iostream>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // First, extract all digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(c)) {
            digits += c;
        }
    }
    
    // Check length and country code
    if (digits.length() == 11) {
        if (digits[0] == '1') {
            digits = digits.substr(1);
        } else {
            throw std::domain_error("invalid number");
        }
    }
    
    // Check if now we have exactly 10 digits
    if (digits.length() != 10) {
        throw std::domain_error("invalid number");
    }
    
    // Check area code (first digit)
    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("invalid area code");
    }
    
    // Check exchange code (fourth digit)
    if (digits[3] < '2' || digits[3] > '9') {
        throw std::domain_error("invalid exchange code");
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

#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // First, extract all digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            digits.push_back(c);
        }
    }
    
    // Check length validity
    if (digits.length() == 11) {
        if (digits[0] != '1') {
            throw std::domain_error("Invalid phone number");
        }
        // Remove the country code
        digits = digits.substr(1);
    } else if (digits.length() != 10) {
        throw std::domain_error("Invalid phone number length");
    }
    
    // Now digits should be exactly 10 characters long
    // Check area code (first digit)
    if ((digits[0] < '2') || (digits[0] > '9')) {
        throw std::domain_error("Area code must start with digit 2-9");
    }
    // Check exchange code (fourth digit)
    if ((digits[3] < '2') || (digits[3] > '9')) {
        throw std::domain_error("Exchange code must start with digit 2-9");
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
    return "(" + cleaned_number.substr(0, 3) + ") " + 
           cleaned_number.substr(3, 3) + "-" + 
           cleaned_number.substr(6);
}

}  // namespace phone_number

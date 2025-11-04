#include "phone_number.h"
#include <string>
#include <stdexcept>
#include <cctype>
#include <algorithm>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // First, extract all digits
    for (char c : raw_number) {
        if (std::isdigit(c)) {
            cleaned_number.push_back(c);
        }
    }
    
    // Check number length
    if (cleaned_number.length() == 11) {
        if (cleaned_number[0] != '1') {
            throw std::domain_error("Invalid number");
        }
        // Remove the country code
        cleaned_number = cleaned_number.substr(1);
    } else if (cleaned_number.length() != 10) {
        throw std::domain_error("Invalid number");
    }
    
    // Now validate area code (NXX)
    if (cleaned_number[0] < '2' || cleaned_number[0] > '9') {
        throw std::domain_error("Invalid number");
    }
    
    // Validate exchange code (NXX)
    if (cleaned_number[3] < '2' || cleaned_number[3] > '9') {
        throw std::domain_error("Invalid number");
    }
}

std::string phone_number::number() const {
    return cleaned_number;
}

std::string phone_number::area_code() const {
    return cleaned_number.substr(0, 3);
}

phone_number::operator std::string() const {
    // Format as NXX-NXX-XXXX
    return "(" + cleaned_number.substr(0, 3) + ") " + 
           cleaned_number.substr(3, 3) + "-" + 
           cleaned_number.substr(6);
}

}  // namespace phone_number

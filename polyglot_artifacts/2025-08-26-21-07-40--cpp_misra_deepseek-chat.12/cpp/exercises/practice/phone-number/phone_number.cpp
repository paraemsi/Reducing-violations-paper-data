#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // Extract all digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            digits.push_back(c);
        }
    }
    
    // Check if the number has a country code
    if (digits.length() == 11) {
        if (digits[0] != '1') {
            throw std::domain_error("Invalid number");
        }
        // Remove the country code
        digits.erase(0, 1);
    }
    
    // Check if we have exactly 10 digits
    if (digits.length() != 10) {
        throw std::domain_error("Invalid number");
    }
    
    // Check area code (NXX) - first digit must be between 2-9
    if (digits[0] == '0' || digits[0] == '1') {
        throw std::domain_error("Invalid number");
    }
    
    // Check exchange code (NXX) - first digit must be between 2-9
    if (digits[3] == '0' || digits[3] == '1') {
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
    // Format as NXX NXX-XXXX
    return "(" + area_code() + ") " + cleaned_number.substr(3, 3) + "-" + cleaned_number.substr(6);
}

}  // namespace phone_number

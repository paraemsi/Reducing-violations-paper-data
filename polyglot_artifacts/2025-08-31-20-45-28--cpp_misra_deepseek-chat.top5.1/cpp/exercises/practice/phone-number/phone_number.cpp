#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // Extract digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(static_cast<unsigned char>(c)) != 0) {
            digits.push_back(c);
        }
    }
    
    // Check length and validity
    if (digits.length() == 11U) {
        if (digits[0] != '1') {
            throw std::domain_error("Invalid number");
        }
        // Remove the country code
        digits = digits.substr(1);
    }
    
    if (digits.length() != 10U) {
        throw std::domain_error("Invalid number");
    }
    
    // Check area code (first digit)
    if ((digits[0] == '0') || (digits[0] == '1')) {
        throw std::domain_error("Invalid number");
    }
    
    // Check exchange code (fourth digit)
    if ((digits[3] == '0') || (digits[3] == '1')) {
        throw std::domain_error("Invalid number");
    }
    
    number_ = digits;
}

std::string phone_number::number() const {
    return number_;
}

std::string phone_number::area_code() const {
    return number_.substr(0, 3);
}

}  // namespace phone_number

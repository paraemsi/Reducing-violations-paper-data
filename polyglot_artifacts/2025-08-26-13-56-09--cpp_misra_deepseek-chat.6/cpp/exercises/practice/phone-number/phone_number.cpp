#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>
#include <cstdint>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // First, extract all digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(static_cast<unsigned char>(c)) != 0) {
            digits.push_back(c);
        }
    }
    
    // Check if the number has a country code
    if ((digits.length()) == 11U) {
        if ((digits[0]) == '1') {
            digits = digits.substr(1);
        } else {
            throw std::domain_error("Invalid country code");
        }
    }
    
    // Check if the number is exactly 10 digits
    if ((digits.length()) != 10U) {
        throw std::domain_error("Invalid phone number length");
    }
    
    // Check area code and exchange code first digits with proper parentheses
    if (((digits[0]) < '2') || ((digits[0]) > '9')) {
        throw std::domain_error("Area code must start with digit 2-9");
    }
    if (((digits[3]) < '2') || ((digits[3]) > '9')) {
        throw std::domain_error("Exchange code must start with digit 2-9");
    }
    
    number_ = digits;
}

std::string phone_number::number() const {
    return number_;
}

}  // namespace phone_number

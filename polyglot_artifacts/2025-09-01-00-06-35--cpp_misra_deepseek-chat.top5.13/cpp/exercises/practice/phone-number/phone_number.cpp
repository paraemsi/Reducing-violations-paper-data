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
        if (std::isdigit(static_cast<unsigned char>(c))) {
            digits.push_back(c);
        }
    }
    
    // Check if the number has a country code
    if (digits.size() == 11U) {
        if (digits[0] == '1') {
            digits = digits.substr(1);
        } else {
            throw std::domain_error("Invalid number");
        }
    }
    
    // Check if we have exactly 10 digits
    if (digits.size() != 10U) {
        throw std::domain_error("Invalid number");
    }
    
    // Check area code (first digit) and exchange code (fourth digit) start with 2-9
    // Using proper parentheses according to rules
    bool area_code_invalid = ((digits[0] < '2') || (digits[0] > '9'));
    bool exchange_code_invalid = ((digits[3] < '2') || (digits[3] > '9'));
    
    if (area_code_invalid || exchange_code_invalid) {
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

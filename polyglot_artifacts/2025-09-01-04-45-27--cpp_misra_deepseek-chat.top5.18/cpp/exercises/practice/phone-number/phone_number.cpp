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
    
    // Check if the number has a country code
    if ((digits.size() == 11) && (digits[0] == '1')) {
        digits = digits.substr(1);
    }
    
    // Check if the number is exactly 10 digits
    if (digits.size() != 10) {
        throw std::domain_error("Invalid number of digits");
    }
    
    // Check area code (first digit) using only equality comparisons
    // Check if it's not between '2' and '9' by checking each invalid case
    if ((digits[0] == '0') || (digits[0] == '1')) {
        throw std::domain_error("Area code cannot start with zero or one");
    }
    
    // Check exchange code (fourth digit) using only equality comparisons
    if ((digits[3] == '0') || (digits[3] == '1')) {
        throw std::domain_error("Exchange code cannot start with zero or one");
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
    return "(" + cleaned_number.substr(0, 3) + ") " + 
           cleaned_number.substr(3, 3) + "-" + 
           cleaned_number.substr(6);
}

}  // namespace phone_number

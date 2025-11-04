#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>

namespace phone_number {

namespace {
bool is_valid_n(char c) {
    // Check if the character is one of '2', '3', '4', '5', '6', '7', '8', '9'
    // Using only equality comparisons
    if ((c == '2') || (c == '3') || (c == '4') || (c == '5') || 
        (c == '6') || (c == '7') || (c == '8') || (c == '9')) {
        return true;
    }
    return false;
}
} // namespace

phone_number::phone_number(const std::string& raw_number) {
    // First, extract all digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            digits.push_back(c);
        }
    }
    
    // Check length
    if (digits.length() == 11) {
        if (digits[0] != '1') {
            throw std::domain_error("Invalid number");
        }
        // Remove the country code
        digits = digits.substr(1);
    }
    
    // Check if the number is now exactly 10 digits
    if (digits.length() != 10) {
        throw std::domain_error("Invalid number");
    }
    
    // Check area code and exchange code using only equality comparisons
    // Area code (first digit): must be valid N
    if (!is_valid_n(digits[0])) {
        throw std::domain_error("Invalid number");
    }
    // Exchange code (fourth digit): must be valid N
    if (!is_valid_n(digits[3])) {
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

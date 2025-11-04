#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>

namespace phone_number {

namespace {

bool is_digit(char c) {
    // Check if the character is a digit using allowed comparisons
    // We can use equality comparisons with character literals
    return ((c == '0') || (c == '1') || (c == '2') || (c == '3') || 
            (c == '4') || (c == '5') || (c == '6') || (c == '7') || 
            (c == '8') || (c == '9'));
}

bool is_valid_nxx_digit(char c) {
    // Check if the character is between '2' and '9' using only equality comparisons
    return ((c == '2') || (c == '3') || (c == '4') || (c == '5') || 
            (c == '6') || (c == '7') || (c == '8') || (c == '9'));
}

} // namespace

phone_number::phone_number(const std::string& raw_number) {
    // First, extract all digits
    std::string digits;
    for (char c : raw_number) {
        if (is_digit(c)) {
            digits.push_back(c);
        }
    }
    
    // Check if the number has a country code
    if (((digits.length() == 11)) && (digits[0] == '1')) {
        digits = digits.substr(1);
    }
    
    // Validate the number
    if (digits.length() != 10) {
        throw std::domain_error("Invalid number of digits");
    }
    
    // Check area code and exchange code using only equality
    if (!is_valid_nxx_digit(digits[0])) {
        throw std::domain_error("Area code cannot start with zero or one");
    }
    if (!is_valid_nxx_digit(digits[3])) {
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

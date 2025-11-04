#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>

namespace phone_number {

namespace {

bool is_valid_nanp_digit(char c) {
    switch (c) {
        case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9':
            return true;
        default:
            return false;
    }
}

}  // namespace

phone_number::phone_number(const std::string& number) {
    // First, extract all digits
    std::string digits;
    for (char c : number) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            digits.push_back(c);
        }
    }
    
    // Check the number of digits
    if (digits.size() == 11) {
        if (digits[0] == '1') {
            cleaned_number = digits.substr(1);
        } else {
            throw std::domain_error("Invalid country code");
        }
    } else if (digits.size() == 10) {
        cleaned_number = digits;
    } else {
        throw std::domain_error("Invalid number of digits");
    }
    
    // Validate we have exactly 10 digits now
    if (cleaned_number.size() != 10) {
        throw std::domain_error("Invalid number");
    }
    
    // Check area code (first digit)
    if (!is_valid_nanp_digit(cleaned_number[0])) {
        throw std::domain_error("Area code cannot start with 0 or 1");
    }
    
    // Check exchange code (fourth digit)
    if (!is_valid_nanp_digit(cleaned_number[3])) {
        throw std::domain_error("Exchange code cannot start with 0 or 1");
    }
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

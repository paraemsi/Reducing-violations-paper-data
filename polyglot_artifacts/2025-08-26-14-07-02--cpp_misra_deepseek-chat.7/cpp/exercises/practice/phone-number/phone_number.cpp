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
    
    // Check length
    if (digits.length() == 11) {
        // Check if the first digit is the country code '1'
        if (digits[0] == '1') {
            // Remove the country code
            digits = digits.substr(1);
        } else {
            throw std::domain_error("Invalid number of digits or country code");
        }
    }
    
    // After processing, the number must be exactly 10 digits
    if (digits.length() != 10) {
        throw std::domain_error("Invalid number of digits");
    }
    
    // Check area code (first digit must be between '2' and '9')
    if ((digits[0] < '2') || (digits[0] > '9')) {
        throw std::domain_error("Area code cannot start with zero or one");
    }
    
    // Check exchange code (fourth digit must be between '2' and '9')
    if ((digits[3] < '2') || (digits[3] > '9')) {
        throw std::domain_error("Exchange code cannot start with zero or one");
    }
    
    number_ = digits;
}

std::string phone_number::number() const {
    return number_;
}

std::string phone_number::area_code() const {
    return number_.substr(0, 3);
}

phone_number::operator std::string() const {
    // Format as (NXX) NXX-XXXX
    return "(" + area_code() + ") " + number_.substr(3, 3) + "-" + number_.substr(6);
}

}  // namespace phone_number

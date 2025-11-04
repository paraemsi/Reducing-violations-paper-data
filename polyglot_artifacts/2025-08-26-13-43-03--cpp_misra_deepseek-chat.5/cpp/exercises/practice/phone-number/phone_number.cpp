#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>
#include <algorithm>

namespace phone_number {

phone_number::phone_number(const std::string& number) {
    // Extract all digits
    std::string digits;
    for (char c : number) {
        if (std::isdigit(c)) {
            digits.push_back(c);
        }
    }
    
    // Check if the number has 11 digits and starts with '1'
    if (digits.length() == 11) {
        if (digits[0] == '1') {
            digits = digits.substr(1);
        } else {
            throw std::domain_error("Invalid number");
        }
    }
    
    // Check if we have exactly 10 digits
    if (digits.length() != 10) {
        throw std::domain_error("Invalid number");
    }
    
    // Check area code (first digit must be between '2' and '9')
    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("Invalid number");
    }
    
    // Check exchange code (fourth digit must be between '2' and '9')
    if (digits[3] < '2' || digits[3] > '9') {
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
    return "(" + area_code() + ") " + cleaned_number.substr(3, 3) + "-" + cleaned_number.substr(6);
}

}  // namespace phone_number

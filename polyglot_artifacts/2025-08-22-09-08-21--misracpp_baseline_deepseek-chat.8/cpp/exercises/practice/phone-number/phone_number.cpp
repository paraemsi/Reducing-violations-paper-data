#include "phone_number.h"
#include <string>
#include <stdexcept>
#include <cctype>
#include <algorithm>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // First, extract all digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(c)) {
            digits.push_back(c);
        }
    }
    
    // Validate number of digits
    if (digits.size() == 11) {
        if (digits[0] != '1') {
            throw std::domain_error("not a valid number");
        }
        // Remove the country code
        digits = digits.substr(1);
    } else if (digits.size() != 10) {
        throw std::domain_error("not a valid number");
    }
    
    // Check area code (first digit)
    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("not a valid number");
    }
    // Check exchange code (fourth digit)
    if (digits[3] < '2' || digits[3] > '9') {
        throw std::domain_error("not a valid number");
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
    return "(" + cleaned_number.substr(0, 3) + ") " + 
           cleaned_number.substr(3, 3) + "-" + 
           cleaned_number.substr(6);
}

}  // namespace phone_number

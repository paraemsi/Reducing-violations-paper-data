#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>
#include <algorithm>
#include <functional>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // Extract all digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(c)) {
            digits.push_back(c);
        }
    }
    
    // Check if the number has a country code
    if (digits.size() == 11) {
        if (digits[0] != '1') {
            throw std::domain_error("Invalid country code");
        }
        // Remove the country code
        digits = digits.substr(1);
    }
    
    // Check if the number is now 10 digits
    if (digits.size() != 10) {
        throw std::domain_error("Invalid number of digits");
    }
    
    // Check area code (first digit)
    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("Area code cannot start with 0 or 1");
    }
    
    // Check exchange code (fourth digit)
    if (digits[3] < '2' || digits[3] > '9') {
        throw std::domain_error("Exchange code cannot start with 0 or 1");
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

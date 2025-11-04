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
    
    // Check length and handle country code
    if (digits.length() == 11) {
        if (digits[0] == '1') {
            digits.erase(0, 1);
        } else {
            throw std::domain_error("Invalid");
        }
    }
    
    // Check if the number now has exactly 10 digits
    if (digits.length() != 10) {
        throw std::domain_error("Invalid");
    }
    
    // Check area code (first digit)
    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("Invalid");
    }
    // Check exchange code (fourth digit)
    if (digits[3] < '2' || digits[3] > '9') {
        throw std::domain_error("Invalid");
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

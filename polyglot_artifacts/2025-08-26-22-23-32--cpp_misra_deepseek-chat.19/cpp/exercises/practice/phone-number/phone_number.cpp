#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // Extract all digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(c)) {
            digits.push_back(c);
        }
    }
    
    // Validate the number of digits and potential country code
    if (digits.length() == 11) {
        if (digits[0] != '1') {
            throw std::domain_error("invalid number");
        }
        // Remove the country code
        digits = digits.substr(1);
    } else if (digits.length() != 10) {
        throw std::domain_error("invalid number");
    }
    
    // Validate area code (NXX) - first digit must be 2-9
    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("invalid number");
    }
    // Validate exchange code (NXX) - fourth digit must be 2-9
    if (digits[3] < '2' || digits[3] > '9') {
        throw std::domain_error("invalid number");
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

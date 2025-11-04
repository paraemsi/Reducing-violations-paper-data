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
    
    // Check if the number has 11 digits and starts with '1'
    if (digits.size() == 11) {
        if (digits[0] == '1') {
            // Remove the country code
            cleaned_number = digits.substr(1, 10);
        } else {
            throw std::domain_error("Invalid number");
        }
    } else if (digits.size() == 10) {
        cleaned_number = digits;
    } else {
        throw std::domain_error("Invalid number");
    }
    
    // Check area code (first digit must be between '2' and '9')
    if (cleaned_number[0] < '2' || cleaned_number[0] > '9') {
        throw std::domain_error("Invalid number");
    }
    // Check exchange code (fourth digit must be between '2' and '9')
    if (cleaned_number[3] < '2' || cleaned_number[3] > '9') {
        throw std::domain_error("Invalid number");
    }
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

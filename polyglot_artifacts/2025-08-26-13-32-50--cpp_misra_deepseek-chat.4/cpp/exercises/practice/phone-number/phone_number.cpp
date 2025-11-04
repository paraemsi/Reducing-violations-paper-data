#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // Extract all digits
    for (char c : raw_number) {
        if (std::isdigit(c)) {
            cleaned_number += c;
        }
    }
    
    // Check length
    if (cleaned_number.length() == 11) {
        if (cleaned_number[0] != '1') {
            throw std::domain_error("11 digits must start with 1");
        }
        // Remove the '1' prefix
        cleaned_number = cleaned_number.substr(1);
    }
    
    // After potential removal, check if we have exactly 10 digits
    if (cleaned_number.length() != 10) {
        throw std::domain_error("Number must be 10 or 11 digits");
    }
    
    // Check area code starts with 2-9
    if (cleaned_number[0] < '2' || cleaned_number[0] > '9') {
        throw std::domain_error("incorrect number of digits");
    }
    
    // Check exchange code starts with 2-9
    if (cleaned_number[3] < '2' || cleaned_number[3] > '9') {
        throw std::domain_error("incorrect number of digits");
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

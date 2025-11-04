#include "phone_number.h"
#include <string>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include <functional>
#include <vector>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // Extract only digits
    for (char c : raw_number) {
        if (std::isdigit(c)) {
            cleaned_number += c;
        }
    }
    
    // Check length
    if (cleaned_number.length() == 11) {
        // Check if the first digit is '1' (valid country code)
        if (cleaned_number[0] != '1') {
            throw std::domain_error("Invalid number");
        }
        // Remove the country code
        cleaned_number = cleaned_number.substr(1);
    }
    
    // After processing, number must be exactly 10 digits
    if (cleaned_number.length() != 10) {
        throw std::domain_error("Invalid number");
    }
    
    // Check area code (first digit)
    if (cleaned_number[0] == '0' || cleaned_number[0] == '1') {
        throw std::domain_error("Invalid number");
    }
    
    // Check exchange code (fourth digit)
    if (cleaned_number[3] == '0' || cleaned_number[3] == '1') {
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

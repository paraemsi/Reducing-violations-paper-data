#include "phone_number.h"
#include <string>
#include <stdexcept>
#include <cctype>
#include <algorithm>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // Extract all digits
    for (char c : raw_number) {
        if (std::isdigit(c)) {
            cleaned_number.push_back(c);
        }
    }
    
    // Check length
    if (cleaned_number.length() == 11) {
        // Check if the first digit is the country code '1'
        if (cleaned_number[0] == '1') {
            // Remove the country code
            cleaned_number = cleaned_number.substr(1);
        } else {
            throw std::domain_error("Invalid number");
        }
    } else if (cleaned_number.length() != 10) {
        throw std::domain_error("Invalid number");
    }
    
    // Now we should have exactly 10 digits
    // Validate area code (first digit)
    if (cleaned_number[0] < '2' || cleaned_number[0] > '9') {
        throw std::domain_error("Invalid number");
    }
    
    // Validate exchange code (fourth digit)
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

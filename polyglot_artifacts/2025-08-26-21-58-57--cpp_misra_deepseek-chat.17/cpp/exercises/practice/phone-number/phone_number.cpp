#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>
#include <algorithm>
#include <functional>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // Extract all digits
    for (char c : raw_number) {
        if (std::isdigit(c)) {
            cleaned_number += c;
        }
    }
    
    // Validate the number
    // Check if the number has 11 digits and starts with '1'
    if (cleaned_number.length() == 11) {
        if (cleaned_number[0] == '1') {
            // Remove the country code
            cleaned_number = cleaned_number.substr(1);
        } else {
            throw std::domain_error("Invalid number");
        }
    }
    // Check if the number now has exactly 10 digits
    if (cleaned_number.length() != 10) {
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
    // Format as (NXX) NXX-XXXX
    return "(" + cleaned_number.substr(0, 3) + ") " + cleaned_number.substr(3, 3) + "-" + cleaned_number.substr(6);
}

}  // namespace phone_number

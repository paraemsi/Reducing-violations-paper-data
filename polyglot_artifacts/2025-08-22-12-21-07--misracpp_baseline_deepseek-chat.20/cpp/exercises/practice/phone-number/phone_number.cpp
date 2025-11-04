#include "phone_number.h"
#include <string>
#include <stdexcept>
#include <cctype>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // Extract all digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(c)) {
            digits.push_back(c);
        }
    }
    
    // Check number length
    if (digits.size() == 11) {
        if (digits[0] != '1') {
            throw std::domain_error("11 digits must start with 1");
        }
        // Remove the country code
        digits = digits.substr(1);
    } else if (digits.size() != 10) {
        throw std::domain_error("Number must be 10 or 11 digits");
    }
    
    // Check area code (NXX)
    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("area code cannot start with zero or one");
    }
    
    // Check exchange code (NXX)
    if (digits[3] < '2' || digits[3] > '9') {
        throw std::domain_error("exchange code cannot start with zero or one");
    }
    
    number_ = digits;
}

std::string phone_number::number() const {
    return number_;
}

std::string phone_number::area_code() const {
    return number_.substr(0, 3);
}

phone_number::operator std::string() const {
    return number_;
}

}  // namespace phone_number

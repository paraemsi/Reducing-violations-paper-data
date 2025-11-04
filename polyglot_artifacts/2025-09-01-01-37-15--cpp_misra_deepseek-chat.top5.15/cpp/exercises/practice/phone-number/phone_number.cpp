#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>
#include <cstdint>

namespace phone_number {

phone_number::phone_number(const std::string& number) {
    // First, extract all digits
    std::string digits;
    for (char c : number) {
        if (std::isdigit(static_cast<unsigned char>(c)) != 0) {
            digits.push_back(c);
        }
    }
    
    // Check length
    const std::size_t len = digits.length();
    if ((len == 11U)) {
        if (digits[0] == '1') {
            digits = digits.substr(1);
        } else {
            throw std::domain_error("Invalid phone number");
        }
    } else {
        if (len != 10U) {
            throw std::domain_error("Invalid phone number length");
        }
    }
    
    // Now digits should be 10 characters long
    // Check area code (first digit)
    if ((digits[0] < '2') || (digits[0] > '9')) {
        throw std::domain_error("Invalid area code");
    }
    // Check exchange code (fourth digit)
    if ((digits[3] < '2') || (digits[3] > '9')) {
        throw std::domain_error("Invalid exchange code");
    }
    
    cleaned_number = digits;
}

std::string phone_number::number() const {
    return cleaned_number;
}

std::string phone_number::area_code() const {
    return cleaned_number.substr(0, 3);
}

}  // namespace phone_number

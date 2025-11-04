#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>
#include <cstdint>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // First, extract all digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            digits.push_back(c);
        }
    }
    
    // Check the number of digits
    if (digits.size() == 11) {
        if (digits[0] == '1') {
            digits = digits.substr(1);
        } else {
            throw std::domain_error("Invalid number");
        }
    } else if (digits.size() != 10) {
        throw std::domain_error("Invalid number");
    }
    
    // Check area code (first digit) is between 2-9 using allowed comparisons
    // Since we can't use relational operators, check each valid value
    const std::string valid_digits = "23456789";
    if (valid_digits.find(digits[0]) == std::string::npos) {
        throw std::domain_error("Invalid area code");
    }
    // Check exchange code (fourth digit) is between 2-9
    if (valid_digits.find(digits[3]) == std::string::npos) {
        throw std::domain_error("Invalid exchange code");
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
    // Format as (NXX) NXX-XXXX
    return "(" + area_code() + ") " + number_.substr(3, 3) + "-" + number_.substr(6);
}

}  // namespace phone_number

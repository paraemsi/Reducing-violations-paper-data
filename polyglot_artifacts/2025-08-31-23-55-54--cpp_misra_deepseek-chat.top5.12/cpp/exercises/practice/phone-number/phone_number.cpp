#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // First, extract all digits
    std::string digits;
    for (char c : raw_number) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            digits.push_back(c);
        }
    }
    
    // Check if the number has a country code
    if ((digits.length() == 11) && (digits[0] == '1')) {
        digits = digits.substr(1);
    }
    
    // Validate the number length
    if (digits.length() != 10) {
        throw std::domain_error("Invalid number length");
    }
    
    // Check area code starts with 2-9 using only equality comparisons
    bool valid_area_code = false;
    if ((digits[0] == '2') || (digits[0] == '3') || (digits[0] == '4') || 
        (digits[0] == '5') || (digits[0] == '6') || (digits[0] == '7') || 
        (digits[0] == '8') || (digits[0] == '9')) {
        valid_area_code = true;
    }
    if (!valid_area_code) {
        throw std::domain_error("Area code must start with digit 2-9");
    }
    
    // Check exchange code starts with 2-9 using only equality comparisons
    bool valid_exchange_code = false;
    if ((digits[3] == '2') || (digits[3] == '3') || (digits[3] == '4') || 
        (digits[3] == '5') || (digits[3] == '6') || (digits[3] == '7') || 
        (digits[3] == '8') || (digits[3] == '9')) {
        valid_exchange_code = true;
    }
    if (!valid_exchange_code) {
        throw std::domain_error("Exchange code must start with digit 2-9");
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
    // Format as NXX NXX-XXXX
    return "(" + area_code() + ") " + number_.substr(3, 3) + "-" + number_.substr(6);
}

}  // namespace phone_number

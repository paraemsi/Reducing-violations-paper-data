#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& input) {
    // First, extract all digits
    std::string digits;
    for (char c : input) {
        if (std::isdigit(static_cast<unsigned char>(c)) != 0) {
            digits.push_back(c);
        }
    }
    
    // Check if the number has a country code
    if (((digits.size() == 11) && (digits[0] == '1'))) {
        digits.erase(0, 1);
    }
    
    // Check if the number now has exactly 10 digits
    if (digits.size() != 10) {
        throw std::domain_error("Invalid number of digits");
    }
    
    // Check area code and exchange code
    // Area code (first digit)
    if (((digits[0] < '2') || (digits[0] > '9'))) {
        throw std::domain_error("Area code cannot start with zero or one");
    }
    
    // Exchange code (fourth digit)
    if (((digits[3] < '2') || (digits[3] > '9'))) {
        throw std::domain_error("Exchange code cannot start with zero or one");
    }
    
    number_ = digits;
}

std::string phone_number::number() const {
    return number_;
}

}  // namespace phone_number

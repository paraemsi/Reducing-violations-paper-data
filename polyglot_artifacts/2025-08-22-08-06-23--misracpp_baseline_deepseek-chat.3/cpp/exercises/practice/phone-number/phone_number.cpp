#include "phone_number.h"
#include <string>
#include <stdexcept>
#include <cctype>

namespace phone_number {

phone_number::phone_number(const std::string& number) {
    std::string cleaned;
    
    // Remove all non-digit characters
    for (char c : number) {
        if (std::isdigit(c)) {
            cleaned += c;
        }
    }
    
    // Check length
    if (cleaned.length() == 11) {
        if (cleaned[0] != '1') {
            throw std::domain_error("11 digits must start with 1");
        }
        // Remove the '1' prefix
        cleaned = cleaned.substr(1);
    }
    
    // After potential removal, check if length is 10
    if (cleaned.length() != 10) {
        throw std::domain_error("must be 10 or 11 digits");
    }
    
    // Check area code (first digit)
    if (cleaned[0] == '0' || cleaned[0] == '1') {
        throw std::domain_error("area code cannot start with zero or one");
    }
    
    // Check exchange code (fourth digit)
    if (cleaned[3] == '0' || cleaned[3] == '1') {
        throw std::domain_error("exchange code cannot start with zero or one");
    }
    
    number_ = cleaned;
}

std::string phone_number::number() const {
    return number_;
}

}  // namespace phone_number

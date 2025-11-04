#include "phone_number.h"
#include <string>
#include <stdexcept>
#include <cctype>
#include <algorithm>
using namespace std;

namespace phone_number {

phone_number::phone_number(const string& raw_number) {
    // Extract all digits
    string digits;
    for (char c : raw_number) {
        if (isdigit(c)) {
            digits.push_back(c);
        }
    }
    
    // Validate the number of digits
    if (digits.size() == 11) {
        if (digits[0] != '1') {
            throw domain_error("Invalid if 11 digits does not start with 1");
        }
        digits = digits.substr(1);
    } else if (digits.size() != 10) {
        throw domain_error("Invalid number of digits");
    }
    
    // Now digits should be exactly 10 digits long
    // Validate area code (first digit)
    if (digits[0] == '0' || digits[0] == '1') {
        throw domain_error("Area code cannot start with zero or one");
    }
    // Validate exchange code (fourth digit)
    if (digits[3] == '0' || digits[3] == '1') {
        throw domain_error("Exchange code cannot start with zero or one");
    }
    
    cleaned_number = digits;
}

string phone_number::number() const {
    return cleaned_number;
}

string phone_number::area_code() const {
    return cleaned_number.substr(0, 3);
}

}  // namespace phone_number

#include "phone_number.h"
#include <string>
#include <stdexcept>
#include <cctype>
#include <algorithm>
using namespace std;

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    // Extract digits and check for invalid characters
    string digits;
    for (char c : raw_number) {
        if (isdigit(c)) {
            digits.push_back(c);
        } else if (isalpha(c)) {
            throw domain_error("letters not permitted");
        }
        // Ignore other characters like '(', ')', '-', '.', ' ', '+'
    }
    
    // Check if the number has a country code
    // Handle '+' by checking if it's present, but since we're only extracting digits, 
    // we need to be careful about the number of digits
    if (digits.size() == 11) {
        if (digits[0] != '1') {
            throw domain_error("11 digits must start with 1");
        }
        // Remove the country code
        digits = digits.substr(1);
    } else if (digits.size() != 10) {
        throw domain_error("incorrect number of digits");
    }
    
    // Now we have exactly 10 digits
    // Check area code (first digit)
    if (digits[0] == '0') {
        throw domain_error("area code cannot start with zero");
    }
    if (digits[0] == '1') {
        throw domain_error("area code cannot start with one");
    }
    
    // Check exchange code (fourth digit)
    if (digits[3] == '0') {
        throw domain_error("exchange code cannot start with zero");
    }
    if (digits[3] == '1') {
        throw domain_error("exchange code cannot start with one");
    }
    
    cleaned_number = digits;
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

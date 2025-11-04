#include "phone_number.h"

#include <cctype>
#include <stdexcept>
#include <string>

namespace phone_number {

std::string clean(const std::string& input) {
    std::string digits;
    digits.reserve(input.size());

    for (std::size_t i = 0; i < input.size(); ++i) {
        char ch = input[i];
        unsigned char uch = static_cast<unsigned char>(ch);

        if (std::isdigit(uch)) {
            digits.push_back(ch);
            continue;
        }

        if (std::isalpha(uch)) {
            throw std::domain_error("letters not permitted");
        }

        // Allowed punctuation characters
        bool allowed_punct = false;
        switch (ch) {
            case ' ':
            case '\t':
            case '-':
            case '.':
            case '(':
            case ')':
                allowed_punct = true;
                break;
            case '+':
                // Leading '+' is allowed (e.g. "+1 613-995-0253").
                allowed_punct = (i == 0);
                break;
            default:
                allowed_punct = false;
        }

        if (!allowed_punct) {
            throw std::domain_error("punctuation not permitted");
        }
    }

    // Validate overall length
    if (digits.size() < 10) {
        throw std::domain_error("incorrect number of digits");
    }
    if (digits.size() > 11) {
        throw std::domain_error("more than 11 digits");
    }
    if (digits.size() == 11) {
        if (digits.front() == '1') {
            digits.erase(digits.begin());  // remove country code
        } else {
            throw std::domain_error("11 digits must start with 1");
        }
    }

    // NANP specific rules (digits is now exactly 10 chars long)
    if (digits[0] == '0') {
        throw std::domain_error("area code cannot start with zero");
    }
    if (digits[0] == '1') {
        throw std::domain_error("area code cannot start with one");
    }
    if (digits[3] == '0') {
        throw std::domain_error("exchange code cannot start with zero");
    }
    if (digits[3] == '1') {
        throw std::domain_error("exchange code cannot start with one");
    }

    return digits;
}

//-----------------------------------------------------------------------------
// phone_number class implementation
//-----------------------------------------------------------------------------

phone_number::phone_number(const std::string& input)
    : digits_(clean(input)) {}

std::string phone_number::number() const {
    return digits_;
}

std::string phone_number::area_code() const {
    return digits_.substr(0, 3);
}

std::string phone_number::pretty() const {
    return "(" + area_code() + ") " + digits_.substr(3, 3) + "-" +
           digits_.substr(6, 4);
}

}  // namespace phone_number

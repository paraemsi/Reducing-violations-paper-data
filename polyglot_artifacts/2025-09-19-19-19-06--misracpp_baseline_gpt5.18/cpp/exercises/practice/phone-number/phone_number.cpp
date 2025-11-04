#include "phone_number.h"

#include <cctype>
#include <stdexcept>

namespace phone_number {

static bool is_valid_start_digit(char c) {
    return c >= '2' && c <= '9';
}

std::string phone_number::sanitize(const std::string& input) {
    std::string digits;
    digits.reserve(input.size());

    for (char ch : input) {
        unsigned char uch = static_cast<unsigned char>(ch);
        if (std::isdigit(uch)) {
            digits.push_back(ch);
        } else if (std::isalpha(uch)) {
            throw std::domain_error("letters not permitted");
        } else {
            switch (ch) {
                case ' ':
                case '.':
                case '-':
                case '(':
                case ')':
                case '+':
                    // allowed punctuation, ignore
                    break;
                default:
                    throw std::domain_error("punctuations not permitted");
            }
        }
    }

    if (digits.size() < 10) {
        throw std::domain_error("incorrect number of digits");
    }
    if (digits.size() == 11) {
        if (digits[0] != '1') {
            throw std::domain_error("11 digits must start with 1");
        }
        // drop leading country code
        digits.erase(digits.begin());
    } else if (digits.size() > 11) {
        throw std::domain_error("more than 11 digits");
    }

    // NANP rules: area code and exchange code cannot start with 0 or 1
    if (!is_valid_start_digit(digits[0])) {
        throw std::domain_error("area code cannot start with zero or one");
    }
    if (!is_valid_start_digit(digits[3])) {
        throw std::domain_error("exchange code cannot start with zero or one");
    }

    return digits;
}

phone_number::phone_number(const std::string& input)
    : number_(sanitize(input)) {}

std::string phone_number::number() const {
    return number_;
}

std::string phone_number::area_code() const {
    return number_.substr(0, 3);
}

std::string phone_number::to_string() const {
    return "(" + number_.substr(0, 3) + ") " + number_.substr(3, 3) + "-" + number_.substr(6, 4);
}

}  // namespace phone_number

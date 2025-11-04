#include "phone_number.h"

#include <cctype>
#include <stdexcept>
#include <string>

namespace phone_number {

namespace {
bool is_allowed_punctuation(char ch) {
    switch (ch) {
        case '+':
        case '(':
        case ')':
        case '-':
        case '.':
            return true;
        default:
            return false;
    }
}
}  // namespace

phone_number::phone_number(const std::string& input) {
    std::string digits;
    digits.reserve(input.size());

    for (char ch : input) {
        unsigned char uch = static_cast<unsigned char>(ch);
        if (std::isdigit(uch)) {
            digits.push_back(static_cast<char>(uch));
        } else if (std::isalpha(uch)) {
            throw std::domain_error("letters not permitted");
        } else if (std::isspace(uch) || is_allowed_punctuation(static_cast<char>(uch))) {
            // allowed - skip
        } else {
            throw std::domain_error("punctuations not permitted");
        }
    }

    if (digits.size() == 11) {
        if (digits[0] == '1') {
            digits.erase(digits.begin());
        } else {
            throw std::domain_error("11 digits must start with 1");
        }
    } else if (digits.size() != 10) {
        throw std::domain_error("incorrect number of digits");
    }

    // NANP rules: area code and exchange code cannot start with 0 or 1
    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("area code cannot start with 0 or 1");
    }
    if (digits[3] < '2' || digits[3] > '9') {
        throw std::domain_error("exchange code cannot start with 0 or 1");
    }

    number_ = std::move(digits);
}

std::string phone_number::number() const {
    return number_;
}

std::string phone_number::area_code() const {
    return number_.substr(0, 3);
}

std::string phone_number::pretty() const {
    return "(" + area_code() + ") " + number_.substr(3, 3) + "-" + number_.substr(6, 4);
}

}  // namespace phone_number

#include "phone_number.h"

#include <cctype>
#include <string>
#include <stdexcept>

namespace phone_number {

namespace {
std::string sanitize(const std::string& input) {
    std::string digits;
    digits.reserve(input.size());

    bool plus_seen = false;
    for (size_t i = 0; i < input.size(); ++i) {
        unsigned char ch = static_cast<unsigned char>(input[i]);
        if (std::isdigit(ch)) {
            digits.push_back(static_cast<char>(ch));
        } else if (ch == ' ' || ch == '(' || ch == ')' || ch == '-' || ch == '.') {
            // allowed separators, ignore
            continue;
        } else if (ch == '+') {
            // '+' is only allowed as the very first character
            if (plus_seen || i != 0) {
                throw std::domain_error("invalid phone number: misplaced '+'");
            }
            plus_seen = true;
        } else {
            // any other letters or punctuation make the number invalid
            throw std::domain_error("invalid phone number: invalid character");
        }
    }

    // Handle optional country code '1'
    if (digits.size() == 11) {
        if (digits.front() != '1') {
            throw std::domain_error("invalid phone number: invalid country code");
        }
        digits.erase(digits.begin());
    } else if (digits.size() != 10) {
        throw std::domain_error("invalid phone number: invalid length");
    }

    // Validate NANP rules (NXX NXX-XXXX, where N is 2-9)
    if (digits[0] < '2') { // area code cannot start with 0 or 1
        throw std::domain_error("invalid phone number: invalid area code");
    }
    if (digits[3] < '2') { // exchange code cannot start with 0 or 1
        throw std::domain_error("invalid phone number: invalid exchange code");
    }

    return digits;
}
} // namespace

phone_number::phone_number(const std::string& input)
    : digits_(sanitize(input)) {}

std::string phone_number::number() const {
    return digits_;
}

std::string phone_number::area_code() const {
    return digits_.substr(0, 3);
}

std::string phone_number::pretty() const {
    return "(" + digits_.substr(0, 3) + ") " + digits_.substr(3, 3) + "-" + digits_.substr(6, 4);
}

}  // namespace phone_number

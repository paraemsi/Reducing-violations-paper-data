#include "phone_number.h"

#include <cctype>
#include <stdexcept>
#include <string>
#include <utility>

namespace phone_number {

namespace {
inline bool is_allowed_punct(char c) {
    switch (c) {
        case ' ':
        case '(':
        case ')':
        case '-':
        case '.':
        case '+':
            return true;
        default:
            return false;
    }
}
}  // namespace

phone_number::phone_number(const std::string& input) {
    std::string digits;
    bool invalid = false;
    digits.reserve(input.size());

    for (char ch : input) {
        unsigned char uch = static_cast<unsigned char>(ch);
        if (std::isdigit(uch)) {
            digits.push_back(static_cast<char>(uch));
        } else if (is_allowed_punct(static_cast<char>(uch))) {
            // ignore allowed punctuation
        } else if (std::isalpha(uch)) {
            invalid = true;  // letters make it invalid
        } else {
            // any other disallowed character makes it invalid
            invalid = true;
        }
    }

    if (!invalid) {
        if (digits.size() == 11) {
            if (digits.front() == '1') {
                digits.erase(digits.begin());  // drop leading country code
            } else {
                invalid = true;
            }
        } else if (digits.size() != 10) {
            invalid = true;
        }
    }

    // NANP: area code and exchange code cannot start with 0 or 1
    if (!invalid) {
        if (digits[0] < '2' || digits[0] > '9') invalid = true;  // area code first digit
        if (digits[3] < '2' || digits[3] > '9') invalid = true;  // exchange code first digit
    }

    if (invalid) {
        throw std::domain_error("invalid phone number");
    }
    normalized_ = std::move(digits);
}

std::string phone_number::number() const {
    return normalized_;
}

std::string phone_number::area_code() const {
    return normalized_.substr(0, 3);
}

std::string phone_number::pretty() const {
    return "(" + normalized_.substr(0, 3) + ") " + normalized_.substr(3, 3) + "-" + normalized_.substr(6, 4);
}

}  // namespace phone_number

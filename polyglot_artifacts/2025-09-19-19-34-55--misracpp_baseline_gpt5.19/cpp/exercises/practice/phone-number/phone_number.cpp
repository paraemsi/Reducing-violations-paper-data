#include "phone_number.h"
#include <cctype>
#include <string>
#include <stdexcept>

namespace phone_number {

static bool is_allowed_punctuation(char c) {
    switch (c) {
        case ' ':
        case '+':
        case '-':
        case '.':
        case '(':
        case ')':
            return true;
        default:
            return false;
    }
}

static bool is_valid_nxx(char c) {
    return c >= '2' && c <= '9';
}

phone_number::phone_number(const std::string& input) : digits_() {
    std::string tmp;
    bool invalid = false;

    for (char ch : input) {
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            tmp.push_back(ch);
        } else if (std::isalpha(static_cast<unsigned char>(ch))) {
            invalid = true;
        } else if (!is_allowed_punctuation(ch) && !std::isspace(static_cast<unsigned char>(ch))) {
            // Neither digit, alpha, allowed punctuation, nor whitespace
            invalid = true;
        }
        // otherwise ignore allowed punctuation/whitespace
    }

    if (!invalid) {
        if (tmp.size() == 11 && tmp.front() == '1') {
            tmp.erase(tmp.begin());
        } else if (tmp.size() != 10) {
            invalid = true;
        }
    }

    if (!invalid) {
        if (!is_valid_nxx(tmp[0]) || !is_valid_nxx(tmp[3])) {
            invalid = true;
        }
    }

    if (invalid) {
        throw std::domain_error("invalid phone number");
    }
    digits_ = std::move(tmp);
}

std::string phone_number::number() const {
    return digits_;
}

std::string phone_number::area_code() const {
    return digits_.substr(0, 3);
}

phone_number::operator std::string() const {
    return "(" + digits_.substr(0, 3) + ") " + digits_.substr(3, 3) + "-" + digits_.substr(6, 4);
}

}  // namespace phone_number

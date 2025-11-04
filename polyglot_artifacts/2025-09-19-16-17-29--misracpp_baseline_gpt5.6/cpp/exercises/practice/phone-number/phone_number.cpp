#include "phone_number.h"
#include <cctype>
#include <stdexcept>

namespace phone_number {

std::string phone_number::only_digits(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (unsigned char ch : s) {
        if (std::isdigit(ch)) {
            out.push_back(static_cast<char>(ch));
        }
    }
    return out;
}

phone_number::phone_number(const std::string& input) {
    // Validate characters: allow digits, spaces, '.', '-', '(', ')', and optional leading '+'
    for (std::size_t i = 0; i < input.size(); ++i) {
        unsigned char ch = static_cast<unsigned char>(input[i]);
        if (std::isalpha(ch)) {
            throw std::domain_error("letters not permitted");
        }
        if (std::isdigit(ch)) {
            continue;
        }
        if (ch == '+') {
            if (i != 0) {
                throw std::domain_error("plus only allowed as leading country code");
            }
            continue;
        }
        switch (ch) {
            case ' ':
            case '.':
            case '-':
            case '(':
            case ')':
                break; // allowed punctuation
            default:
                throw std::domain_error("punctuation not permitted");
        }
    }

    std::string digits = only_digits(input);

    // Length checks
    if (digits.size() < 10) {
        throw std::domain_error("incorrect number of digits");
    }
    if (digits.size() > 11) {
        throw std::domain_error("more than 11 digits");
    }
    if (digits.size() == 11) {
        if (digits.front() != '1') {
            throw std::domain_error("11 digits must start with 1");
        }
        // Drop leading country code '1'
        digits.erase(digits.begin());
    }

    // Validate NANP: 10 digits, area code and exchange code cannot start with 0 or 1
    if (!(digits.size() == 10 &&
          (digits[0] >= '2' && digits[0] <= '9') &&
          (digits[3] >= '2' && digits[3] <= '9'))) {
        throw std::domain_error("invalid NANP number");
    }

    digits_ = digits;
}

std::string phone_number::number() const {
    return digits_;
}

std::string phone_number::area_code() const {
    if (digits_.size() >= 3) {
        return digits_.substr(0, 3);
    }
    return std::string();
}

std::string phone_number::pretty() const {
    if (digits_.size() == 10) {
        return "(" + digits_.substr(0, 3) + ") " + digits_.substr(3, 3) + "-" + digits_.substr(6, 4);
    }
    return digits_;
}

}  // namespace phone_number

#include "phone_number.h"

#include <cctype>
#include <string>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& input) {
    std::string digits;
    digits.reserve(input.size());
    bool invalid = false;
    bool seen_non_space = false;

    for (char c : input) {
        unsigned char uc = static_cast<unsigned char>(c);
        if (std::isdigit(uc)) {
            digits.push_back(static_cast<char>(uc));
            seen_non_space = true;
        } else if (std::isspace(uc) || uc == '(' || uc == ')' || uc == '-' || uc == '.') {
            // Allowed punctuation and formatting, ignore.
            if (!std::isspace(uc)) {
                seen_non_space = true;
            }
        } else if (uc == '+') {
            if (seen_non_space) {
                invalid = true;
            } else {
                // Leading plus is allowed.
                seen_non_space = true;
            }
        } else {
            invalid = true;
        }
    }

    if (!invalid) {
        if (digits.size() == 11) {
            if (digits.front() == '1') {
                digits.erase(digits.begin());
            } else {
                invalid = true;
            }
        }
        if (digits.size() != 10) {
            invalid = true;
        }
        if (!invalid) {
            // NANP constraints: area and exchange codes cannot start with 0 or 1.
            if (digits[0] < '2' || digits[0] > '9') {
                invalid = true;
            }
            if (digits[3] < '2' || digits[3] > '9') {
                invalid = true;
            }
        }
    }

    if (invalid) {
        throw std::domain_error("invalid phone number");
    }
    digits_ = digits;
}

std::string phone_number::number() const {
    return digits_;
}

std::string phone_number::area_code() const {
    return digits_.substr(0, 3);
}

std::string phone_number::pretty() const {
    return "(" + area_code() + ") " + digits_.substr(3, 3) + "-" + digits_.substr(6, 4);
}

}  // namespace phone_number

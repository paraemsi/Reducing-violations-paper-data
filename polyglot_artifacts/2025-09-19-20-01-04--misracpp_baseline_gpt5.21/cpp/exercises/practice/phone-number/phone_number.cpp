#include "phone_number.h"
#include <cctype>
#include <stdexcept>

namespace phone_number {

static inline bool is_allowed_punctuation(unsigned char c) {
    return c == ' ' || c == '-' || c == '.' || c == '(' || c == ')';
}

std::string clean(const std::string& input) {
    std::string digits;
    digits.reserve(input.size());

    bool plus_seen = false;
    for (std::size_t i = 0; i < input.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(input[i]);
        if (std::isdigit(c)) {
            digits.push_back(static_cast<char>(c));
        } else if (c == '+') {
            if (i != 0 || plus_seen) {
                throw std::domain_error("invalid leading '+' placement");
            }
            plus_seen = true;
        } else if (is_allowed_punctuation(c)) {
            continue;
        } else {
            throw std::domain_error("invalid character in phone number");
        }
    }

    // Handle country code
    if (digits.size() == 11) {
        if (digits[0] != '1') {
            throw std::domain_error("invalid country code");
        }
        digits.erase(digits.begin());
    } else if (digits.size() != 10) {
        throw std::domain_error("invalid number of digits");
    }

    // NANP validation: area code and exchange code cannot start with 0 or 1
    if (digits[0] < '2' || digits[0] > '9') {
        throw std::domain_error("invalid area code");
    }
    if (digits[3] < '2' || digits[3] > '9') {
        throw std::domain_error("invalid exchange code");
    }

    return digits;
}

}  // namespace phone_number

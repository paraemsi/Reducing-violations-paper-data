#include "phone_number.h"

#include <cctype>
#include <stdexcept>
#include <string>

namespace phone_number {

phone_number::phone_number(const std::string& input) {
    std::string digits;
    digits.reserve(input.size());

    for (std::size_t i = 0; i < input.size(); ++i) {
        unsigned char ch = static_cast<unsigned char>(input[i]);
        if (std::isdigit(ch)) {
            digits.push_back(static_cast<char>(ch));
        } else if (std::isalpha(ch)) {
            // letters are not permitted in phone numbers
            throw std::domain_error("letters not permitted in phone number");
        } else {
            // ignore any other non-digit character (punctuation/whitespace/symbols)
            continue;
        }
    }

    if (digits.size() == 11) {
        if (digits[0] != '1') {
            throw std::domain_error("11-digit numbers must start with country code '1'");
        }
        // remove leading country code
        digits.erase(digits.begin());
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

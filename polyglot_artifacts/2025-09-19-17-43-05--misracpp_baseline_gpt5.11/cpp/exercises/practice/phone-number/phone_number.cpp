#include "phone_number.h"

#include <cctype>
#include <string>
#include <stdexcept>

namespace phone_number {

namespace {
    constexpr char TWO = '2';
    constexpr char NINE = '9';
    const std::string zeros = "0000000000";

    bool valid_nanp(const std::string& digits) {
        return digits.size() == 10 &&
               digits[0] >= TWO && digits[0] <= NINE &&      // area code first digit 2-9
               digits[3] >= TWO && digits[3] <= NINE;        // exchange code first digit 2-9
    }
}

phone_number::phone_number(const std::string& input) : cleaned_(zeros) {
    std::string digits;
    digits.reserve(input.size());

    bool invalid = false;
    bool seen_plus = false;
    for (std::size_t i = 0; i < input.size(); ++i) {
        unsigned char uch = static_cast<unsigned char>(input[i]);
        char ch = static_cast<char>(uch);
        if (std::isdigit(uch)) {
            digits.push_back(ch);
        } else if (ch == ' ' || ch == '(' || ch == ')' || ch == '.' || ch == '-') {
            continue; // allowed punctuation
        } else if (ch == '+') {
            // allow a single leading '+'
            if (i != 0 || seen_plus) {
                invalid = true;
                break;
            }
            seen_plus = true;
        } else if (std::isalpha(uch)) {
            invalid = true;
            break;
        } else {
            // any other symbol is invalid
            invalid = true;
            break;
        }
    }

    if (invalid) {
        throw std::domain_error("invalid phone number");
    }

    if (digits.size() < 10) {
        throw std::domain_error("invalid phone number");
    }
    if (digits.size() > 11) {
        throw std::domain_error("invalid phone number");
    }
    if (digits.size() == 11) {
        if (digits.front() != '1') {
            throw std::domain_error("invalid phone number");
        }
        digits.erase(0, 1);
    }

    if (!valid_nanp(digits)) {
        throw std::domain_error("invalid phone number");
    }

    cleaned_ = digits;
}

std::string phone_number::number() const {
    return cleaned_;
}

std::string phone_number::area_code() const {
    return cleaned_.substr(0, 3);
}

std::string phone_number::pretty() const {
    return "(" + area_code() + ") " + cleaned_.substr(3, 3) + "-" + cleaned_.substr(6);
}

}  // namespace phone_number

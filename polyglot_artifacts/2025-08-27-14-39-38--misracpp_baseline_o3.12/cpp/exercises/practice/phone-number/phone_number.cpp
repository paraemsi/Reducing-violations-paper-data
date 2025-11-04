#include "phone_number.h"

#include <cctype>
#include <cstddef>
#include <stdexcept>

namespace phone_number {

static constexpr std::size_t NANP_LENGTH = 10;

static bool is_allowed_punctuation(char c) {
    return c == ' ' || c == '.' || c == '-' || c == '(' || c == ')' || c == '+';
}

static std::string extract_digits(const std::string &input) {
    std::string digits;
    digits.reserve(input.size());
    for (char c : input) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            digits.push_back(c);
        } else if (!is_allowed_punctuation(c)) {
            throw std::domain_error("invalid character in phone number");
        }
    }
    return digits;
}

bool phone_number::is_valid(const std::string &digits) {
    if (digits.size() != NANP_LENGTH) {
        return false;
    }
    // Area code first digit must be 2-9
    if (digits[0] < '2' || digits[0] > '9') {
        return false;
    }
    // Exchange code first digit must be 2-9
    if (digits[3] < '2' || digits[3] > '9') {
        return false;
    }
    return true;
}

phone_number::phone_number(const std::string &input) {
    std::string digits = extract_digits(input);

    // Handle 11-digit numbers that start with country code '1'
    if (digits.size() == NANP_LENGTH + 1) {
        if (digits.front() == '1') {
            digits.erase(digits.begin());
        } else {
            throw std::domain_error("11-digit numbers must start with 1");
        }
    }

    if (digits.size() != NANP_LENGTH) {
        throw std::domain_error("incorrect number of digits");
    }

    if (!is_valid(digits)) {
        throw std::domain_error("invalid NANP number");
    }

    number_ = digits;
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

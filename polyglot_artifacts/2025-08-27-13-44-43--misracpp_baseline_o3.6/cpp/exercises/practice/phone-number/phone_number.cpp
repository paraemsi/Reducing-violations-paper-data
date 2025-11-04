#include "phone_number.h"
#include <cctype>
#include <stdexcept>

namespace phone_number {

namespace {

// Validate NANP rules for area and exchange codes.
bool is_valid(const std::string& digits) {
    if (digits.size() != 10) {
        return false;
    }
    // Area code (NXX) cannot start with 0 or 1
    if (digits[0] < '2' || digits[0] > '9') {
        return false;
    }
    // Exchange code (NXX) cannot start with 0 or 1
    if (digits[3] < '2' || digits[3] > '9') {
        return false;
    }
    return true;
}

} // anonymous namespace

// Remove punctuation, optional leading country code, then validate.
std::string phone_number::clean(const std::string& raw) {
    std::string digits;
    digits.reserve(raw.size());

    for (char ch : raw) {
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            digits.push_back(ch);
        } else if (std::isalpha(static_cast<unsigned char>(ch))) {
            throw std::domain_error("letters not permitted");
        } else if (ch == ' ' || ch == '.' || ch == '-' || ch == '(' || ch == ')' || ch == '+') {
            // Allowed separator characters – ignore.
            continue;
        } else {
            throw std::domain_error("punctuations not permitted");
        }
    }

    // Handle optional leading country code
    if (digits.size() == 11) {
        if (digits.front() == '1') {
            digits.erase(digits.begin());
        } else {
            throw std::domain_error("11 digits must start with 1");
        }
    } else if (digits.size() != 10) {
        throw std::domain_error("incorrect number of digits");
    }

    if (!is_valid(digits)) {
        throw std::domain_error("area or exchange code invalid");
    }

    return digits;
}

// Constructor
phone_number::phone_number(const std::string& raw)
    : digits_{clean(raw)} {}

// Return the cleaned 10-digit number
std::string phone_number::number() const {
    return digits_;
}

// Return the 3-digit area code
std::string phone_number::area_code() const {
    return digits_.substr(0, 3);
}

// Return "(NXX) NXX-XXXX" representation
std::string phone_number::pretty() const {
    return "(" + area_code() + ") " + digits_.substr(3, 3) + "-" + digits_.substr(6);
}

} // namespace phone_number

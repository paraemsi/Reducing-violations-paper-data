#include "phone_number.h"

#include <string>
#include <cctype>
#include <stdexcept>

namespace phone_number {

namespace {
bool is_permitted_punctuation(char c) {
    switch (c) {
        case ' ':
        case '.':
        case '-':
        case '(':
        case ')':
        case '+':
            return true;
        default:
            return false;
    }
}

std::string clean(const std::string& raw) {
    std::string digits;
    digits.reserve(raw.size());

    for (char c : raw) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            digits.push_back(c);
        } else if (std::isalpha(static_cast<unsigned char>(c))) {
            throw std::domain_error("letters not permitted");
        } else if (!is_permitted_punctuation(c)) {
            throw std::domain_error("punctuations not permitted");
        }
    }
    return digits;
}
}  // namespace

phone_number::phone_number(const std::string& raw) {
    digits_ = clean(raw);

    if (digits_.size() == 11 && digits_[0] == '1') {
        digits_.erase(digits_.begin());
    } else if (digits_.size() == 11) {
        throw std::domain_error("11 digits must start with 1");
    }

    if (digits_.size() < 10) {
        throw std::domain_error("incorrect number of digits");
    }
    if (digits_.size() > 10) {
        throw std::domain_error("more than 11 digits");
    }

    if (digits_[0] < '2' || digits_[0] > '9') {
        throw std::domain_error("area code cannot start with zero or one");
    }
    if (digits_[3] < '2' || digits_[3] > '9') {
        throw std::domain_error("exchange code cannot start with zero or one");
    }
}

std::string phone_number::number() const {
    return digits_;
}

std::string phone_number::area_code() const {
    return digits_.substr(0, 3);
}

std::string phone_number::pretty() const {
    return "(" + digits_.substr(0, 3) + ") " + digits_.substr(3, 3) + "-" + digits_.substr(6);
}

}  // namespace phone_number

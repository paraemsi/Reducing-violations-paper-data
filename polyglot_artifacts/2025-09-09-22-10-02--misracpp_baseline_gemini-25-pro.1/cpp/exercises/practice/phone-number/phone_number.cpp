#include "phone_number.h"

#include <cctype>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& raw_number) {
    std::string digits;
    for (const char c : raw_number) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            digits.push_back(c);
        } else if (c != '(' && c != ')' && c != '-' && c != '.' && c != ' ' && c != '+') {
            throw std::domain_error("invalid character in phone number");
        }
    }

    if (digits.length() == 11) {
        if (digits.at(0) == '1') {
            cleaned_number = digits.substr(1);
        } else {
            throw std::domain_error("11-digit number must start with 1");
        }
    } else if (digits.length() == 10) {
        cleaned_number = digits;
    } else {
        throw std::domain_error("Number must be 10 or 11 digits");
    }

    if (cleaned_number.at(0) < '2') {
        throw std::domain_error("Area code cannot start with 0 or 1");
    }
    if (cleaned_number.at(3) < '2') {
        throw std::domain_error("Exchange code cannot start with 0 or 1");
    }
}

std::string phone_number::number() const {
    return cleaned_number;
}

std::string phone_number::area_code() const {
    return cleaned_number.substr(0, 3);
}

phone_number::operator std::string() const {
    return "(" + area_code() + ") " + cleaned_number.substr(3, 3) + "-" + cleaned_number.substr(6);
}

}  // namespace phone_number

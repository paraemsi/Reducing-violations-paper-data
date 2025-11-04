#include "phone_number.h"

#include <cctype>
#include <string>
#include <stdexcept>

namespace {

std::string clean(const std::string& text) {
    std::string temp_number{};
    for (const char c : text) {
        if (std::isdigit(static_cast<unsigned char>(c)) != 0) {
            temp_number += c;
        }
    }

    if (temp_number.length() == 11U) {
        if (temp_number.at(0) == '1') {
            temp_number = temp_number.substr(1);
        } else {
            throw std::domain_error("11-digit number must start with 1");
        }
    }

    if (temp_number.length() != 10U) {
        throw std::domain_error("incorrect number of digits");
    }

    const char area_code_first_digit = temp_number.at(0);
    if (area_code_first_digit == '0') {
        throw std::domain_error("area code cannot start with zero");
    }
    if (area_code_first_digit == '1') {
        throw std::domain_error("area code cannot start with one");
    }

    const char exchange_code_first_digit = temp_number.at(3);
    if (exchange_code_first_digit == '0') {
        throw std::domain_error("exchange code cannot start with zero");
    }
    if (exchange_code_first_digit == '1') {
        throw std::domain_error("exchange code cannot start with one");
    }

    return temp_number;
}

} // namespace

namespace phone_number {

phone_number::phone_number(const std::string& text)
    : cleaned_number{clean(text)} {}

phone_number::operator std::string() const {
    return "(" + cleaned_number.substr(0, 3) + ") " +
           cleaned_number.substr(3, 3) + "-" + cleaned_number.substr(6, 4);
}

}  // namespace phone_number

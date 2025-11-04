#include "phone_number.h"

#include <cctype>
#include <string>
#include <stdexcept>

namespace phone_number {


std::string clean_number(const std::string& input)
{
    std::string digits{};
    digits.reserve(input.size());

    for (char ch : input) {
        if ((std::isalpha(std::char_traits<char>::to_int_type(ch)) != 0)) {
            throw std::domain_error("letters not permitted");
        }

        if ((std::isdigit(std::char_traits<char>::to_int_type(ch)) != 0)) {
            digits.push_back(ch);
        } else {
            if (((ch == ' ') || (ch == '(') || (ch == ')') || (ch == '-') || (ch == '.') || (ch == '+'))) {
                // permitted punctuation/spacing, ignore
            } else {
                throw std::domain_error("punctuation not permitted");
            }
        }
    }

    if ((digits.size() == static_cast<std::string::size_type>(11U))) {
        if ((digits.front() == '1')) {
            digits.erase(digits.begin());
        } else {
            throw std::domain_error("11 digits must start with 1");
        }
    }

    if ((digits.size() != static_cast<std::string::size_type>(10U))) {
        throw std::domain_error("incorrect number of digits");
    }

    if (((digits[0] == '0') || (digits[0] == '1'))) {
        throw std::domain_error("area code cannot start with 0 or 1");
    }

    if (((digits[3] == '0') || (digits[3] == '1'))) {
        throw std::domain_error("exchange code cannot start with 0 or 1");
    }

    return digits;
}

phone_number::phone_number(const std::string& input)
    : digits_{clean_number(input)}
{
}

std::string phone_number::number() const noexcept
{
    return digits_;
}

}  // namespace phone_number

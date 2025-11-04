#include "phone_number.h"
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <string>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(std::string const& input)
{
    std::string digits {};
    for (char c : input) {
        if ((std::isdigit(std::char_traits<char>::to_int_type(c)) != 0)) {
            digits.push_back(c);
        } else {
            if ((c == ' ') || (c == '-') || (c == '.') || (c == '(') || (c == ')') || (c == '+')) {
                // allowed punctuation and whitespace
            } else if ((std::isalpha(std::char_traits<char>::to_int_type(c)) != 0)) {
                throw std::domain_error("letters not permitted");
            } else {
                throw std::domain_error("punctuation not permitted");
            }
        }
    }

    if ((digits.size() == static_cast<std::size_t>(11))) {
        if ((digits.front() == '1')) {
            digits.erase(static_cast<std::size_t>(0), static_cast<std::size_t>(1));
        } else {
            throw std::domain_error("11 digits must start with 1");
        }
    } else if ((digits.size() == static_cast<std::size_t>(10))) {
        // ok
    } else {
        throw std::domain_error("incorrect number of digits");
    }

    if (((digits.at(static_cast<std::size_t>(0)) == '0')) || ((digits.at(static_cast<std::size_t>(0)) == '1'))) {
        throw std::domain_error("area code cannot start with 0 or 1");
    }
    if (((digits.at(static_cast<std::size_t>(3)) == '0')) || ((digits.at(static_cast<std::size_t>(3)) == '1'))) {
        throw std::domain_error("exchange code cannot start with 0 or 1");
    }

    digits_ = digits;
}

auto phone_number::number() const noexcept -> std::string
{
    return digits_;
}

auto number(std::string const& input) -> std::string
{
    return phone_number(input).number();
}

}  // namespace phone_number

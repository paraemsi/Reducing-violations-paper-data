#include "phone_number.h"

#include <cctype>
#include <cstdint>
#include <stdexcept>
#include <string>

namespace phone_number {

auto clean(const std::string& input) -> std::string
{
    std::string digits;
    digits.reserve(input.size());

    bool saw_plus = false;

    for (const char ch : input) {
        if (ch == '+') {
            if ((digits.empty()) && (saw_plus == false)) {
                saw_plus = true;
            } else {
                throw std::domain_error("invalid '+' placement");
            }
        } else if ((std::isdigit(std::char_traits<char>::to_int_type(ch)) != 0)) {
            digits.push_back(ch);
        } else if ((ch == '(') || (ch == ')') || (ch == '.') || (ch == '-') || (std::isspace(std::char_traits<char>::to_int_type(ch)) != 0)) {
            // ignore permitted punctuation/whitespace
        } else {
            throw std::domain_error("invalid character in phone number");
        }
    }

    if (digits.size() == static_cast<std::size_t>(11)) {
        if (digits.front() == '1') {
            digits.erase(static_cast<std::size_t>(0), static_cast<std::size_t>(1));
        } else {
            throw std::domain_error("11-digit numbers must start with country code 1");
        }
    } else if (digits.size() != static_cast<std::size_t>(10)) {
        throw std::domain_error("incorrect number of digits");
    }

    // NANP constraint: area code and exchange code cannot start with 0 or 1
    if ((digits[0] == '0') || (digits[0] == '1')) {
        throw std::domain_error("invalid area code");
    }

    if ((digits[3] == '0') || (digits[3] == '1')) {
        throw std::domain_error("invalid exchange code");
    }

    return digits;
}

phone_number::phone_number(const std::string& input)
    : digits_{clean(input)}
{
}

auto phone_number::number() const -> std::string
{
    return digits_;
}

auto phone_number::area_code() const -> std::string
{
    return digits_.substr(static_cast<std::size_t>(0), static_cast<std::size_t>(3));
}

phone_number::operator std::string() const
{
    std::string out;
    out.reserve(static_cast<std::size_t>(14));
    out.push_back('(');
    out.append(digits_, static_cast<std::size_t>(0), static_cast<std::size_t>(3));
    out.append(") ");
    out.append(digits_, static_cast<std::size_t>(3), static_cast<std::size_t>(3));
    out.push_back('-');
    out.append(digits_, static_cast<std::size_t>(6), static_cast<std::size_t>(4));
    return out;
}

}  // namespace phone_number

#include "phone_number.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <utility>
#include <stdexcept>

namespace {

/* Return true if character c is one of the decimal digits 0-9 */
auto is_decimal_digit(char c) -> bool
{
    const auto val{std::char_traits<char>::to_int_type(c)};
    return (val >= std::char_traits<char>::to_int_type('0')) &&
           (val <= std::char_traits<char>::to_int_type('9'));
}

} // unnamed namespace

namespace phone_number {

/* ***************************************** */
/*  phone_number private helpers             */
/* ***************************************** */

auto phone_number::clean(const std::string& input) -> std::string
{
    std::string digits{};
    digits.reserve(input.length());

    for (char c : input) {
        if (is_decimal_digit(c)) {
            digits.push_back(c);
        }
    }

    /* Remove NANP country code ‘1’ if present */
    if ((digits.length() == static_cast<std::size_t>(11U)) && (digits[0] == '1')) {
        digits.erase(0, 1);
    }

    /* Validate resulting sequence; throw when invalid */
    if (!is_valid(digits)) {
        throw std::domain_error("invalid phone number");
    }

    return digits;
}

auto phone_number::is_valid(const std::string& digits) -> bool
{
    if (digits.length() != static_cast<std::size_t>(10U)) {
        return false;
    }

    const auto area_first{std::char_traits<char>::to_int_type(digits[0])};
    if ((area_first < std::char_traits<char>::to_int_type('2')) ||
        (area_first > std::char_traits<char>::to_int_type('9'))) {
        return false;
    }

    const auto exchange_first{std::char_traits<char>::to_int_type(digits[3])};
    if ((exchange_first < std::char_traits<char>::to_int_type('2')) ||
        (exchange_first > std::char_traits<char>::to_int_type('9'))) {
        return false;
    }

    return true;
}

/* ***************************************** */
/*  Constructors                             */
/* ***************************************** */

phone_number::phone_number(const std::string& input)
    : m_number(clean(input))
{
}

/* ***************************************** */
/*  Public API                               */
/* ***************************************** */

auto phone_number::number() const -> std::string
{
    return m_number;
}

auto phone_number::area_code() const -> std::string
{
    return m_number.substr(0, 3);
}

auto phone_number::pretty() const -> std::string
{
    /* (XXX) XXX-XXXX */
    std::string formatted{"("};
    formatted.append(m_number.substr(0, 3));
    formatted.append(") ");
    formatted.append(m_number.substr(3, 3));
    formatted.append("-");
    formatted.append(m_number.substr(6, 4));
    return formatted;
}

}  // namespace phone_number

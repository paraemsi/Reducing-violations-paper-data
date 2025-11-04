#include "phone_number.h"

#include <cstddef>
#include <stdexcept>

namespace phone_number {

namespace {

/* Helper: build digit-only string from raw input */
std::string extract_digits(const std::string& raw)
{
    std::string digits {};
    digits.reserve(raw.size());

    for (char ch : raw) {
        constexpr char digit_list[] = {
            '0', '1', '2', '3', '4',
            '5', '6', '7', '8', '9'
        };

        for (char d : digit_list) {
            if (ch == d) {
                digits.push_back(ch);
                break;
            }
        }
    }

    return digits;
}

}  // namespace


bool phone_number::phone_number::is_valid(const std::string& digits)
{
    /* Must be exactly ten digits after country-code handling */
    if (digits.size() != static_cast<std::size_t>(10)) {
        return false;
    }

    /* Area code (first digit) may not be 0 or 1 */
    if ((digits[0] == '0') || (digits[0] == '1')) {
        return false;
    }

    /* Exchange code (fourth digit) may not be 0 or 1 */
    if ((digits[3] == '0') || (digits[3] == '1')) {
        return false;
    }

    return true;
}

phone_number::phone_number::phone_number(const std::string& raw)
{
    std::string digits {extract_digits(raw)};

    /* Validate length and optional leading country code */
    if (digits.size() == static_cast<std::size_t>(11)) {
        if (digits[0] == '1') {
            digits.erase(0, static_cast<std::size_t>(1));
        } else {
            throw std::domain_error{"invalid number"};
        }
    } else if (digits.size() != static_cast<std::size_t>(10)) {
        throw std::domain_error{"invalid number"};
    }

    /* Structural validation (area/exchange codes) */
    if (!is_valid(digits)) {
        throw std::domain_error{"invalid number"};
    }

    cleaned_ = digits;
}

std::string phone_number::phone_number::number() const
{
    return cleaned_;
}

std::string phone_number::phone_number::area_code() const
{
    return cleaned_.substr(static_cast<std::size_t>(0), static_cast<std::size_t>(3));
}

std::string phone_number::phone_number::pretty() const
{
    return "(" + area_code() + ") "
           + cleaned_.substr(static_cast<std::size_t>(3), static_cast<std::size_t>(3))
           + "-"
           + cleaned_.substr(static_cast<std::size_t>(6), static_cast<std::size_t>(4));
}

}  // namespace phone_number

#include "phone_number.h"

#include <array>
#include <stdexcept>

namespace phone_number {

namespace {

/* Helper to check if character is one of the ten decimal digits.
 * Equality comparisons between characters are permitted by the rules. */
constexpr bool is_digit_char(char c) noexcept
{
    /* NOLINTNEXTLINE(readability-magic-numbers) */
    constexpr std::array<char, 10U> digits{{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}};
    for (char d : digits) {
        if (c == d) {
            return true;
        }
    }
    return false;
}

/* Helper for validating that the first digit of an area / exchange code is 2-9. */
constexpr bool is_valid_first_digit_char(char c) noexcept
{
    /* NOLINTNEXTLINE(readability-magic-numbers) */
    constexpr std::array<char, 8U> valid_digits{{'2', '3', '4', '5', '6', '7', '8', '9'}};
    for (char d : valid_digits) {
        if (c == d) {
            return true;
        }
    }
    return false;
}

} // unnamed namespace


bool phone_number::is_digit(char c) noexcept
{
    return is_digit_char(c);
}

bool phone_number::is_valid_first_digit(char c) noexcept
{
    return is_valid_first_digit_char(c);
}

phone_number::phone_number(std::string_view input)
{
    std::string digits;
    digits.reserve(input.size());

    for (char ch : input) {
        if (is_digit(ch) != false) {
            digits.push_back(ch);
        }
    }

    /* Validate length and optional country code. */
    if (digits.size() == static_cast<std::size_t>(11U)) {
        if (digits[0] == '1') {
            digits.erase(0U, 1U);
        } else {
            throw std::domain_error("invalid phone number");
        }
    } else if (digits.size() != static_cast<std::size_t>(10U)) {
        throw std::domain_error("invalid phone number");
    }

    /* Validate leading digits of area code and exchange code. */
    if ((!is_valid_first_digit(digits[0])) || (!is_valid_first_digit(digits[3]))) {
        throw std::domain_error("invalid phone number");
    }

    m_clean_number = digits;
}

std::string phone_number::number() const
{
    return m_clean_number;
}

std::string phone_number::area_code() const
{
    return m_clean_number.substr(0U, 3U);
}

std::string phone_number::pretty() const
{
    return "(" + area_code() + ") " + m_clean_number.substr(3U, 3U) + "-" + m_clean_number.substr(6U, 4U);
}

}  // namespace phone_number

#include "phone_number.h"
#include <cstddef>
#include <stdexcept>

namespace phone_number {

namespace {

/* Helper: identify a decimal digit without evaluating the character’s
 * numeric value (MISRA compliant). */
[[nodiscard]] constexpr bool is_digit_char(const char c) noexcept
{
    return ((c == '0') || (c == '1') || (c == '2') || (c == '3') ||
            (c == '4') || (c == '5') || (c == '6') || (c == '7') ||
            (c == '8') || (c == '9'));
}

} // namespace

phone_number::phone_number(const std::string& raw_input)
{
    std::string digits;
    digits.reserve(raw_input.length());

    for(const char c : raw_input) {
        if(is_digit_char(c)) {
            digits.push_back(c);
        }
    }

    if((digits.size() == static_cast<std::size_t>(11U)) &&
       (digits.front() == '1')) {
        digits.erase(0U, 1U);
    }

    bool valid {false};

    if(digits.size() == static_cast<std::size_t>(10U)) {
        const bool area_valid { (digits[0] != '0') && (digits[0] != '1') };
        const bool exchange_valid { (digits[3] != '0') && (digits[3] != '1') };
        if(area_valid && exchange_valid) {
            valid = true;
        }
    }

    if(valid) {
        m_clean = digits;
    } else {
        throw std::domain_error("invalid phone number");
    }
}

std::string phone_number::number() const
{
    return m_clean;
}

std::string phone_number::area_code() const
{
    return m_clean.substr(0U, 3U);
}

std::string phone_number::pretty() const
{
    return "(" + area_code() + ") " +
           m_clean.substr(3U, 3U) + "-" +
           m_clean.substr(6U, 4U);
}

}  // namespace phone_number

#include "phone_number.h"
#include <cstddef>
#include <string>
#include <stdexcept>

namespace phone_number {

auto clean(const std::string& input) -> std::string
{
    /* Gather just the decimal digits, ignoring all other characters */
    std::string digits{};
    digits.reserve(input.size());

    for (const char c : input)
    {
        if ((c == '0') || (c == '1') || (c == '2') || (c == '3') || (c == '4') ||
            (c == '5') || (c == '6') || (c == '7') || (c == '8') || (c == '9'))
        {
            digits.push_back(c);
        }
    }

    /* Remove leading country code ‘1’ when present */
    if ((digits.size() == static_cast<std::size_t>(11U)) && (digits.front() == '1'))
    {
        digits.erase(digits.begin());
    }

    /* Must be exactly ten digits after optional country code removal */
    if (digits.size() != static_cast<std::size_t>(10U))
    {
        return std::string{};
    }

    /* Validate NANP rules:
       - Area-code first digit (index 0) must be 2-9
       - Exchange-code first digit (index 3) must be 2-9
       Equality comparisons are MISRA-compliant. */
    if ((digits[0] == '0') || (digits[0] == '1'))
    {
        return std::string{};
    }

    if ((digits[3] == '0') || (digits[3] == '1'))
    {
        return std::string{};
    }

    return digits;
}

/* phone_number class implementation */

phone_number::phone_number(const std::string& input)
    : m_number{}
{
    m_number = clean(input);
    if (m_number.empty())
    {
        throw std::domain_error("invalid phone number");
    }
}

auto phone_number::number() const -> std::string
{
    return m_number;
}

auto phone_number::area_code() const -> std::string
{
    return m_number.substr(static_cast<std::size_t>(0U), static_cast<std::size_t>(3U));
}

auto phone_number::pretty() const -> std::string
{
    return '(' + m_number.substr(static_cast<std::size_t>(0U), static_cast<std::size_t>(3U)) + ") " +
           m_number.substr(static_cast<std::size_t>(3U), static_cast<std::size_t>(3U)) + '-' +
           m_number.substr(static_cast<std::size_t>(6U), static_cast<std::size_t>(4U));
}

}  // namespace phone_number

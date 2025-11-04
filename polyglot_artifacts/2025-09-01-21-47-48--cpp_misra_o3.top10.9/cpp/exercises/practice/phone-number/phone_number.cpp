#include "phone_number.h"

#include <string>
#include <cstddef>
#include <stdexcept>

namespace phone_number {

namespace {

/* Return the standard invalid-phone marker. */
inline auto invalid_number() -> std::string
{
    return std::string{"0000000000"};
}

/* Locale-independent digit test complying with MISRA rules. */
inline bool is_digit_character(const char ch) noexcept
{
    const auto value = std::char_traits<char>::to_int_type(ch);
    const auto zero  = std::char_traits<char>::to_int_type('0');
    const auto nine  = std::char_traits<char>::to_int_type('9');

    return ((value >= zero) && (value <= nine));
}

} // unnamed namespace

auto phone_number::clean(const std::string& raw) -> std::string
{
    std::string digits_only{};
    digits_only.reserve(raw.size());

    for (const char ch : raw)
    {
        if (is_digit_character(ch))
        {
            digits_only.push_back(ch);
        }
    }

    /* Handle optional country code. */
    if (digits_only.size() == static_cast<std::size_t>(11U))
    {
        if (digits_only.front() == '1')
        {
            digits_only.erase(0U, 1U);
        }
        else
        {
            throw std::domain_error("invalid phone number");
        }
    }
    else if (digits_only.size() != static_cast<std::size_t>(10U))
    {
        throw std::domain_error("invalid phone number");
    }

    /* Validate area and exchange codes do not start with 0 or 1. */
    if ((digits_only[0] == '0') || (digits_only[0] == '1') ||
        (digits_only[3] == '0') || (digits_only[3] == '1'))
    {
        throw std::domain_error("invalid phone number");
    }

    return digits_only;
}

phone_number::phone_number(const std::string& raw) : m_number{clean(raw)}
{
}

auto phone_number::number() const -> std::string
{
    return m_number;
}

auto phone_number::area_code() const -> std::string
{
    return m_number.substr(0U, 3U);
}

phone_number::operator std::string() const
{
    std::string formatted{};
    formatted.reserve(14U); /* "(xxx) xxx-xxxx" */

    formatted.push_back('(');
    formatted.append(m_number, 0U, 3U);
    formatted.append(") ");
    formatted.append(m_number, 3U, 3U);
    formatted.push_back('-');
    formatted.append(m_number, 6U, 4U);

    return formatted;
}

}  // namespace phone_number

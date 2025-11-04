#include "phone_number.h"

#include <cstdint>
#include <string>
#include <stdexcept>

namespace phone_number {

namespace {

/* Helper: true if ch is decimal digit ('0'-'9') */
constexpr bool is_digit_char(char ch) noexcept
{
    const std::int32_t value = std::char_traits<char>::to_int_type(ch);
    const std::int32_t zero  = std::char_traits<char>::to_int_type('0');
    const std::int32_t nine  = std::char_traits<char>::to_int_type('9');
    return ((value >= zero) && (value <= nine));
}

/* Sanitize raw user input per NANP rules, else throw std::domain_error */
[[nodiscard]] std::string sanitize(const std::string& input)
{
    std::string digits {};
    digits.reserve(input.size());

    for (char ch : input)
    {
        if (is_digit_char(ch))
        {
            digits.push_back(ch);
        }
        else
        {
            /* ignore punctuation / spacing */
        }
    }

    if ((digits.size() == static_cast<std::size_t>(11)) && (digits.front() == '1'))
    {
        digits.erase(digits.begin()); /* strip country code */
    }

    const bool length_is_valid = (digits.size() == static_cast<std::size_t>(10));
    const bool area_code_valid = ((digits.size() >= static_cast<std::size_t>(1))
                               && (digits[0] != '0')
                               && (digits[0] != '1'));
    const bool exchange_code_valid = ((digits.size() >= static_cast<std::size_t>(4))
                                   && (digits[3] != '0')
                                   && (digits[3] != '1'));

    if ((!length_is_valid) || (!area_code_valid) || (!exchange_code_valid))
    {
        throw std::domain_error("invalid NANP phone number");
    }

    return digits;
}

} // unnamed namespace

phone_number::phone_number(const std::string& raw)
    : m_digits{sanitize(raw)}
{
}

std::string phone_number::number() const
{
    return m_digits;
}

std::string phone_number::area_code() const
{
    return m_digits.substr(0, 3);
}

std::string phone_number::pretty() const
{
    std::string formatted{"("};
    formatted += m_digits.substr(0, 3);
    formatted += ") ";
    formatted += m_digits.substr(3, 3);
    formatted += '-';
    formatted += m_digits.substr(6, 4);
    return formatted;
}

}  // namespace phone_number

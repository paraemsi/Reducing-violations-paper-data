#include "phone_number.h"
#include <cstdint>
#include <string>
#include <stdexcept>

namespace phone_number {

namespace   /* unnamed */ {

/*  Return true if ch is one of the decimal digits. */
static auto is_digit_char(const char ch) -> bool
{
    switch (ch)
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return true;
        default:
            return false;
    }
}

/*  Return true if ch is in the range '2'-'9' inclusive. */
static auto is_between_2_and_9(const char ch) -> bool
{
    switch (ch)
    {
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return true;
        default:
            return false;
    }
}

} /* unnamed namespace */

auto clean(const std::string& input) -> std::string
{
    std::string digits {};
    digits.reserve(input.size());

    for (const char ch : input)
    {
        if (is_digit_char(ch))
        {
            digits.push_back(ch);
        }
        else
        {
            /* non-digit characters are ignored */
        }
    }

    if (digits.size() == static_cast<std::string::size_type>(11U))
    {
        if (digits.front() == '1')
        {
            digits.erase(0U, 1U);
        }
        else
        {
            throw std::domain_error("Invalid country code");
        }
    }

    if (digits.size() != static_cast<std::string::size_type>(10U))
    {
        throw std::domain_error("Incorrect number of digits");
    }

    if ((is_between_2_and_9(digits.at(0U)) == false) ||
        (is_between_2_and_9(digits.at(3U)) == false))
    {
        throw std::domain_error("Invalid area or exchange code");
    }

    return digits;
}

/* ---------------- phone_number class implementation ---------------- */

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
    return digits_.substr(0U, 3U);
}

auto phone_number::pretty() const -> std::string
{
    std::string formatted {};
    formatted.reserve(14U); /* "(XXX) XXX-XXXX" */

    formatted.push_back('(');
    formatted.append(digits_.substr(0U, 3U));
    formatted.append(") ");
    formatted.append(digits_.substr(3U, 3U));
    formatted.push_back('-');
    formatted.append(digits_.substr(6U, 4U));

    return formatted;
}

}  // namespace phone_number

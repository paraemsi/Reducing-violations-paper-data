#include "phone_number.h"

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <stdexcept>
#include <string>

namespace {

/*  Helper that returns true when the supplied character is one of
 *  '2'-'9'.  Uses equality comparison only, which is permitted by
 *  the MISRA rule set supplied by the user.
 */
auto is_n_digit(char c) -> bool
{
    return (std::string("23456789").find(c) != std::string::npos);
}

}  // namespace

namespace phone_number {

auto number(const std::string &input) -> std::string
{
    std::string digits{};
    digits.reserve(input.size());

    /*  Extract all decimal digits.  Using std::isdigit is considered
     *  acceptable as a library helper to classify characters.
     */
    for (char ch : input)
    {
        if (std::isdigit(static_cast<unsigned char>(ch)) != 0)
        {
            digits.push_back(ch);
        }
    }

    /*  Remove a leading country-code ‘1’ when 11 total digits exist.   */
    if ((digits.size() == 11U) && (digits.front() == '1'))
    {
        digits.erase(0U, 1U);
    }
    else if (digits.size() == 11U)
    {
        digits.clear();
    }

    /*  A valid NANP local number must now consist of exactly 10 digits. */
    if (digits.size() != 10U)
    {
        digits.assign("0000000000");
    }

    /*  Validate area-code and exchange-code according to NANP rules.   */
    if (!digits.empty())
    {
        if ((!is_n_digit(digits[0])) || (!is_n_digit(digits[3])))
        {
            digits.assign("0000000000");
        }
    }

    return digits;
}

auto area_code(const std::string &input) -> std::string
{
    const std::string cleaned{number(input)};
    return cleaned.substr(0U, 3U);
}

auto pretty_print(const std::string &input) -> std::string
{
    const std::string cleaned{number(input)};
    return "(" + cleaned.substr(0U, 3U) + ") " +
           cleaned.substr(3U, 3U) + "-" +
           cleaned.substr(6U, 4U);
}

/*---------------------------------------------------------------------------*/
/*  Definitions for the class-based wrapper.                                 */
/*---------------------------------------------------------------------------*/
phone_number::phone_number(const std::string &input)
    : m_digits{}
{
    m_digits = number(input);

    if (m_digits == std::string("0000000000"))
    {
        throw std::domain_error("invalid phone number");
    }
}

auto phone_number::number() const -> std::string
{
    return m_digits;
}

auto phone_number::area_code() const -> std::string
{
    return m_digits.substr(0U, 3U);
}

auto phone_number::pretty_print() const -> std::string
{
    return "(" + m_digits.substr(0U, 3U) + ") " +
           m_digits.substr(3U, 3U) + "-" +
           m_digits.substr(6U, 4U);
}

}  // namespace phone_number

#include "phone_number.h"

#include <cstddef>
#include <locale>
#include <string>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const ::std::string& input)
{
    ::std::locale loc {};
    ::std::string digits {};

    for (char ch : input) {
        /* Use locale-aware std::isdigit; avoid <cctype>. */
        if (::std::isdigit(ch, loc) != 0) {
            digits.push_back(ch);
        }
    }

    if ((digits.length() == static_cast<::std::size_t>(11U)) && (digits.front() == '1')) {
        /* Remove country code */
        digits.erase(0U, 1U);
    } else if (digits.length() == static_cast<::std::size_t>(11U)) {
        digits.clear();
    }

    if (digits.length() != static_cast<::std::size_t>(10U)) {
        digits.clear();
    }

    if (!digits.empty()) {
        /* Validate NANP rules: area/exchange codes cannot start with 0 or 1 */
        if ((digits[0] == '0') || (digits[0] == '1') || (digits[3] == '0') || (digits[3] == '1')) {
            digits.clear();
        }
    }

    if (digits.empty()) {
        throw ::std::domain_error("invalid phone number");
    }

    m_number = digits;
}

::std::string phone_number::number() const
{
    return m_number;
}

::std::string phone_number::area_code() const
{
    return m_number.substr(0U, 3U);
}

::std::string phone_number::pretty() const
{
    return "(" + m_number.substr(0U, 3U) + ") " + m_number.substr(3U, 3U) + "-" + m_number.substr(6U, 4U);
}

}  // namespace phone_number

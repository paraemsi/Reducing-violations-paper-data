#include "phone_number.h"
#include <cstddef>   /* for std::size_t */
#include <stdexcept> /* for std::domain_error */

namespace phone_number {

namespace {

/* List of valid digit characters */
const std::string digits_chars { "0123456789" };

/* The first digit of the area and exchange codes must be 2-9 */
const std::string significant_first_digit { "23456789" };

/*-----------------------------------------------------------------------------
 *  Remove non-digit characters, strip optional country code,
 *  and validate NANP rules.
 *---------------------------------------------------------------------------*/
auto clean_input(const std::string& raw) -> std::string
{
    std::string result {};
    result.reserve(raw.size());

    for (char c : raw) {
        if (digits_chars.find(c) != std::string::npos) {
            result.push_back(c);
        } else {
            /* ignore character that is not a digit */
        }
    }

    /* Remove leading country code '1' when length is 11 */
    if ((result.size() == static_cast<std::size_t>(11U)) && (result.front() == '1')) {
        result.erase(0, 1);
    }

    /* Must be exactly 10 digits after processing */
    if (result.size() != static_cast<std::size_t>(10U)) {
        throw std::domain_error("invalid phone number");
    }

    /* Area code and exchange code may not start with 0 or 1 */
    if ((significant_first_digit.find(result[0]) == std::string::npos) ||
        (significant_first_digit.find(result[3]) == std::string::npos)) {
        throw std::domain_error("invalid phone number");
    }

    return result;
}

}   /* unnamed namespace */

phone_number::phone_number(const std::string& raw)
    : cleaned_number_ { clean_input(raw) }
{
}

auto phone_number::number() const -> std::string
{
    return cleaned_number_;
}

auto phone_number::area_code() const -> std::string
{
    return cleaned_number_.substr(0U, 3U);
}

auto phone_number::pretty() const -> std::string
{
    return "(" + cleaned_number_.substr(0U, 3U) + ") " +
           cleaned_number_.substr(3U, 3U) + "-" +
           cleaned_number_.substr(6U, 4U);
}

}  // namespace phone_number

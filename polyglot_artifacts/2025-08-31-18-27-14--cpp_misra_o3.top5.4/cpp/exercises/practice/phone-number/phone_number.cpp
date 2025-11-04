#include "phone_number.h"

#include <cctype>     // for std::isdigit
#include <cstdint>    // fixed-width integer types
#include <cstddef>    // for std::size_t
#include <sstream>    // for std::ostringstream
#include <string>
#include <stdexcept>  // for std::domain_error

namespace {

/*  Helper: extract only the decimal digits from the supplied string. */
PN_NODISCARD auto only_digits(const std::string& source) -> std::string
{
    std::string result{};
    for (const char ch : source)
    {
        /*  std::isdigit expects an unsigned char cast to int.
         *  The cast is explicit to comply with MISRA. */
        if (std::isdigit(static_cast<unsigned char>(ch)) != 0)
        {
            result.push_back(ch);
        }
    }
    return result;
}

/*  Helper: test NANP validity rules for the 10-digit string. */
PN_NODISCARD auto is_valid_nanp(const std::string& digits) -> bool
{
    return ((digits.length() == static_cast<std::size_t>(10U)) &&
            /* Area code must not start with 0 or 1 */
            ((digits[0] != '0') && (digits[0] != '1')) &&
            /* Exchange code must not start with 0 or 1 */
            ((digits[3] != '0') && (digits[3] != '1')));
}

/*  Helper: fully clean the supplied string and return validated digits. */
PN_NODISCARD auto clean_digits(const std::string& input) -> std::string
{
    std::string digits{only_digits(input)};

    if ((digits.length() == static_cast<std::size_t>(11U)) && (digits.front() == '1'))
    {
        digits.erase(static_cast<std::size_t>(0U), static_cast<std::size_t>(1U));
    }

    if (!is_valid_nanp(digits))
    {
        throw std::domain_error("invalid NANP phone number");
    }

    return digits;
}

} // namespace

namespace phone_number {

phone_number::phone_number(const std::string& input)
    : digits_{clean_digits(input)}
{
}

auto phone_number::number() const -> std::string
{
    return digits_;
}

auto phone_number::area_code() const -> std::string
{
    return digits_.substr(static_cast<std::size_t>(0U), static_cast<std::size_t>(3U));
}

auto phone_number::pretty() const -> std::string
{
    std::ostringstream oss{};
    oss << '(' << digits_.substr(static_cast<std::size_t>(0U), static_cast<std::size_t>(3U))
        << ") "
        << digits_.substr(static_cast<std::size_t>(3U), static_cast<std::size_t>(3U))
        << '-'
        << digits_.substr(static_cast<std::size_t>(6U), static_cast<std::size_t>(4U));
    return oss.str();
}

} // namespace phone_number

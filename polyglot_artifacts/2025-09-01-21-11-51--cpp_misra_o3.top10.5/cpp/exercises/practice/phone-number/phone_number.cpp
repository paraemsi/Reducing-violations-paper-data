#include "phone_number.h"

#include <cstddef>
#include <locale>
#include <string>
#include <stdexcept>

namespace phone_number {

namespace
{
/* Helper to check if a digit character is in the inclusive range '2'–'9'.
 * Equality comparisons on characters are permitted by the MISRA-inspired rules,
 * whereas relational comparisons on characters are not. */
constexpr bool is_two_to_nine(const char ch) noexcept
{
    return (ch == '2') || (ch == '3') || (ch == '4') ||
           (ch == '5') || (ch == '6') || (ch == '7') ||
           (ch == '8') || (ch == '9');
}
} // anonymous namespace

phone_number::phone_number(const std::string& input)
{
    std::string only_digits{};
    only_digits.reserve(input.size());

    const ::std::locale loc{};

    for (const char ch : input)
    {
        /* std::isdigit from <locale> is permitted */
        if (::std::isdigit(ch, loc) != 0)
        {
            only_digits.push_back(ch);
        }
    }

    constexpr ::std::size_t eleven{11U};
    constexpr ::std::size_t ten{10U};

    if ((only_digits.size() == eleven) && (only_digits.front() == '1'))
    {
        /* remove leading country code */
        only_digits.erase(0, 1);
    }

    bool valid{true};

    if (only_digits.size() != ten)
    {
        valid = false;
    }

    if (valid)
    {
        const char area_first{only_digits[0]};
        const char exchange_first{only_digits[3]};

        if ((!is_two_to_nine(area_first)) || (!is_two_to_nine(exchange_first)))
        {
            valid = false;
        }
    }

    if (valid)
    {
        digits_ = only_digits;
    }
    else
    {
        throw ::std::domain_error("invalid phone number");
    }
}

std::string phone_number::number() const
{
    return digits_;
}

std::string phone_number::area_code() const
{
    return digits_.substr(0, 3U);
}

std::string phone_number::pretty() const
{
    return '(' + digits_.substr(0, 3U) + ") " +
           digits_.substr(3U, 3U) + '-' +
           digits_.substr(6U, 4U);
}

}  // namespace phone_number

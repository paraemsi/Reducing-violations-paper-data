#include "phone_number.h"

#include <cstddef>
#include <string>
#include <stdexcept>

namespace phone_number {

namespace {

/* Helper that returns true when the supplied character is one of the
 * decimal digits ‘0’–‘9’.  Equality comparisons on character operands
 * are permitted by the coding rules, whereas relational comparisons
 * are not.
 */
constexpr bool is_decimal_digit(char ch) noexcept
{
    return (
        (ch == '0') || (ch == '1') || (ch == '2') || (ch == '3') ||
        (ch == '4') || (ch == '5') || (ch == '6') || (ch == '7') ||
        (ch == '8') || (ch == '9')
    );
}

} // namespace

/* Constructor – cleans the supplied input and stores either a
 * validated ten–digit string or the all-zero invalid sentinel.
 */
phone_number::phone_number(const std::string& input_number)
{
    std::string only_digits{};
    only_digits.reserve(input_number.size());

    for (const char ch : input_number) {
        if (is_decimal_digit(ch)) {
            only_digits.push_back(ch);
        }
    }

    /* Handle optional country code ‘1’ when the total length is 11. */
    if (((only_digits.size() == static_cast<std::size_t>(11)) &&
         (only_digits.front() == '1'))) {
        only_digits.erase(only_digits.begin());
    }

    /* Validate final digit sequence – must be exactly ten digits with
     * area/exchange codes that do not start with 0 or 1.
     */
    if ((only_digits.size() != static_cast<std::size_t>(10)) ||
        (!is_valid_area_and_exchange(only_digits))) {
        throw std::domain_error("invalid phone number");
    }

    digits_ = only_digits;
}

std::string phone_number::number() const
{
    return digits_;
}

std::string phone_number::area_code() const
{
    return digits_.substr(static_cast<std::size_t>(0), static_cast<std::size_t>(3));
}

std::string phone_number::pretty() const
{
    const std::string area{ area_code() };
    const std::string exchange{ digits_.substr(static_cast<std::size_t>(3), static_cast<std::size_t>(3)) };
    const std::string subscriber{ digits_.substr(static_cast<std::size_t>(6), static_cast<std::size_t>(4)) };

    return "(" + area + ") " + exchange + "-" + subscriber;
}


/* static */ bool phone_number::is_valid_length(const std::string& digits) noexcept
{
    return (digits.size() == static_cast<std::size_t>(10));
}

/* static */ bool phone_number::is_valid_area_and_exchange(const std::string& digits) noexcept
{
    if (!is_valid_length(digits)) {
        return false;
    }

    const bool valid_area{ (digits[0] != '0') && (digits[0] != '1') };
    const bool valid_exchange{ (digits[3] != '0') && (digits[3] != '1') };

    return (valid_area && valid_exchange);
}

}  // namespace phone_number

#include "phone_number.h"

#include <cctype>
#include <cstddef>
#include <stdexcept>
#include <string>

namespace {

/* Sanitize the user-supplied phone number and validate it against the
 * North American Numbering Plan rules.
 */
auto sanitize_input(const std::string &input) -> std::string
{
    std::string digits{};
    digits.reserve(input.size());

    for (char c : input) {
        if (std::isdigit(std::char_traits<char>::to_int_type(c)) != 0) {
            digits.push_back(c);
        }
    }

    if ((digits.size() == static_cast<std::size_t>(11U)) && (digits[0] == '1')) {
        digits.erase(0U, 1U); /* remove leading country code */
    }

    if (digits.size() != static_cast<std::size_t>(10U)) {
        throw std::domain_error("invalid phone number length");
    }

    constexpr const char * valid_first_digits = "23456789";

    if (std::string(valid_first_digits).find(digits[0]) == std::string::npos) {
        throw std::domain_error("invalid area code");
    }

    if (std::string(valid_first_digits).find(digits[3]) == std::string::npos) {
        throw std::domain_error("invalid exchange code");
    }

    return digits;
}

}  // anonymous namespace

namespace phone_number {

/*------------------------------------------------------------
 *  phone_number class implementation
 *----------------------------------------------------------*/
phone_number::phone_number(const std::string &input)
    : cleaned_number_(sanitize_input(input))
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

auto phone_number::pretty_print() const -> std::string
{
    return "(" + cleaned_number_.substr(0U, 3U) + ") "
           + cleaned_number_.substr(3U, 3U) + "-"
           + cleaned_number_.substr(6U, 4U);
}




}  // namespace phone_number

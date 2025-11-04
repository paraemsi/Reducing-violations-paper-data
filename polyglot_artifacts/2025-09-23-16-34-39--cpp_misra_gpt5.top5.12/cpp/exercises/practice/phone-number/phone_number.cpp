#include "phone_number.h"

#include <cctype>
#include <stdexcept>
#include <string>
#include <string_view>

namespace phone_number {

static std::string strip_to_digits(const std::string& input)
{
    std::string digits{};
    digits.reserve(input.size());

    for (const char ch : input) {
        const std::char_traits<char>::int_type c_int = std::char_traits<char>::to_int_type(ch);
        if (std::isdigit(c_int) != 0) {
            digits.push_back(ch);
        } else {
            // ignore non-digits, including '+' and punctuation
        }
    }

    return digits;
}

std::string phone_number::invalid_number() noexcept
{
    return std::string("0000000000");
}

bool phone_number::is_valid_area_or_exchange_start_char(char ch) noexcept
{
    // Valid start is any digit except '0' or '1'
    return ((ch != '0') && (ch != '1'));
}

std::string phone_number::clean(const std::string& input)
{
    std::string digits = strip_to_digits(input);

    if (digits.size() == static_cast<std::size_t>(11U)) {
        if (digits[0] == '1') {
            digits.erase(static_cast<std::size_t>(0U), static_cast<std::size_t>(1U));
        } else {
            throw std::domain_error("invalid");
        }
    } else if (digits.size() == static_cast<std::size_t>(10U)) {
        // OK
    } else {
        throw std::domain_error("invalid");
    }

    // Validate NANP rules: area code and exchange code cannot start with '0' or '1'
    if ((!is_valid_area_or_exchange_start_char(digits[0])) || (!is_valid_area_or_exchange_start_char(digits[3]))) {
        throw std::domain_error("invalid");
    }

    return digits;
}

phone_number::phone_number(const std::string& input)
    : digits_{clean(input)}
{
    // digits_ is now either 10 digits or "0000000000"
}

std::string phone_number::number() const
{
    return digits_;
}

std::string phone_number::area_code() const
{
    return digits_.substr(static_cast<std::size_t>(0U), static_cast<std::size_t>(3U));
}

phone_number::operator std::string() const
{
    std::string formatted{};
    formatted.reserve(static_cast<std::size_t>(14U));
    formatted.push_back('(');
    formatted.append(area_code());
    formatted.append(") ");
    formatted.append(digits_.substr(static_cast<std::size_t>(3U), static_cast<std::size_t>(3U)));
    formatted.push_back('-');
    formatted.append(digits_.substr(static_cast<std::size_t>(6U), static_cast<std::size_t>(4U)));
    return formatted;
}

}  // namespace phone_number

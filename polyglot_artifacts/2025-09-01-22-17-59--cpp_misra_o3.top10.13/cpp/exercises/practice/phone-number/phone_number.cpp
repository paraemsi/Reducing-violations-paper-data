#include "phone_number.h"

#include <cstddef>
#include <stdexcept>

namespace phone_number {

constexpr bool phone_number::is_digit_char(char ch) noexcept
{
    switch (ch) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            return true;
        default:
            return false;
    }
}

bool phone_number::has_valid_prefix(const std::string& num) noexcept
{
    /*  Area code (index 0) and exchange code (index 3) must not be 0 or 1 */
    return ((num[0] != '0') && (num[0] != '1') &&
            (num[3] != '0') && (num[3] != '1'));
}

phone_number::phone_number(const std::string& input)
{
    std::string cleaned{};
    cleaned.reserve(input.size());

    /*  Keep only digit characters */
    for (const char ch : input) {
        if (is_digit_char(ch)) {
            cleaned.push_back(ch);
        }
    }

    /*  Handle optional country code */
    if (cleaned.size() == static_cast<std::size_t>(11U)) {
        if (cleaned.front() == '1') {
            cleaned.erase(static_cast<std::size_t>(0U), static_cast<std::size_t>(1U));
        } else {
            throw std::domain_error("invalid phone number");
        }
    }

    /*  Must now contain exactly 10 digits */
    if (cleaned.size() != static_cast<std::size_t>(10U)) {
        throw std::domain_error("invalid phone number");
    }

    /*  Validate area and exchange codes */
    if (!has_valid_prefix(cleaned)) {
        throw std::domain_error("invalid phone number");
    }

    digits_ = cleaned;
}

std::string phone_number::number() const
{
    return digits_;
}

std::string phone_number::area_code() const
{
    return digits_.substr(static_cast<std::string::size_type>(0U),
                          static_cast<std::string::size_type>(3U));
}

std::string phone_number::pretty() const
{
    return "(" + area_code() + ") " +
           digits_.substr(static_cast<std::string::size_type>(3U),
                          static_cast<std::string::size_type>(3U)) +
           "-" +
           digits_.substr(static_cast<std::string::size_type>(6U),
                          static_cast<std::string::size_type>(4U));
}

}  // namespace phone_number

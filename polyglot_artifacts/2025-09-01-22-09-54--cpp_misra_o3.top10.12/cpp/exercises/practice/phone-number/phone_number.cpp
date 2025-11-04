#include "phone_number.h"

#include <cstddef>      // for std::size_t
#include <cstdint>      // fixed-width integer types (rule compliance)
#include <stdexcept>    // for std::invalid_argument
#include <string>
#include <locale>       // for std::isalpha, std::locale

namespace phone_number {

auto clean(const std::string& input) -> std::string
{
    std::string digits{};
    digits.reserve(input.size());

    const std::locale loc{};
    for(const char c : input)
    {
        if (std::isalpha(c, loc))
        {
            throw std::invalid_argument("invalid phone number");
        }

        switch(c)
        {
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                digits.push_back(c);
                break;
            /* permitted punctuation and spacing characters, simply ignore */
            case ' ': case '(': case ')': case '.': case '-': case '+':
                break;
            /* any other character renders the phone number invalid */
            default:
                throw std::invalid_argument("invalid phone number");
        }
    }

    /* Handle optional NANP country code '1' (or '+1' already stripped) */
    if ((digits.size() == static_cast<std::size_t>(11U)) && (digits[0] == '1'))
    {
        digits.erase(0, static_cast<std::size_t>(1U));
    }

    bool invalid {false};

    if (digits.size() != static_cast<std::size_t>(10U))
    {
        invalid = true;
    }
    else
    {
        /* Validate area code and exchange code first digits (cannot be 0 or 1) */
        if ((digits[0] == '0') || (digits[0] == '1'))
        {
            invalid = true;
        }

        if ((digits[3] == '0') || (digits[3] == '1'))
        {
            invalid = true;
        }
    }

    if (invalid)
    {
        throw std::invalid_argument("invalid phone number");
    }

    return digits;
}

/* ------------------------------------------------------------------------ */
/* phone_number class implementation                                       */
/* ------------------------------------------------------------------------ */
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
    return digits_.substr(static_cast<std::size_t>(0U), static_cast<std::size_t>(3U));
}

auto phone_number::pretty() const -> std::string
{
    std::string formatted{};
    formatted.reserve(static_cast<std::size_t>(14U));

    formatted += '(';
    formatted += digits_.substr(static_cast<std::size_t>(0U), static_cast<std::size_t>(3U));
    formatted += ") ";
    formatted += digits_.substr(static_cast<std::size_t>(3U), static_cast<std::size_t>(3U));
    formatted += '-';
    formatted += digits_.substr(static_cast<std::size_t>(6U), static_cast<std::size_t>(4U));

    return formatted;
}

}  // namespace phone_number

#include "phone_number.h"

#include <cctype>
#include <cstddef>
#include <string>
#include <stdexcept>

namespace phone_number {

namespace {

// Determines if the digit is prohibited as the first digit of
// an area or exchange code (must not be '0' or '1').
bool is_prohibited_first_digit(char c) noexcept
{
    return (c == '0') || (c == '1');
}

} // anonymous namespace

bool phone_number::is_digit(char c) noexcept
{
    /* std::isdigit expects an unsigned char value or EOF, so cast explicitly */
    return (std::isdigit(static_cast<unsigned char>(c)) != 0);
}

phone_number::phone_number(const std::string& raw_number)
    : number_{}
{
    std::string digits;
    digits.reserve(raw_number.size());

    for (char ch : raw_number)
    {
        if (is_digit(ch))
        {
            digits.push_back(ch);
        }
        else
        {
            /* Accept common formatting punctuation and whitespace; anything
             * else renders the input invalid.
             */
            if ((ch == ' ')  || (ch == '\t') || (ch == '(') || (ch == ')') ||
                (ch == '-')  || (ch == '.') || (ch == '+'))
            {
                /* ignore allowed non-digit formatting characters */
            }
            else
            {
                throw std::domain_error("invalid phone number");
            }
        }
    }

    if ((digits.size() == static_cast<std::size_t>(11)) && (digits.front() == '1'))
    {
        digits.erase(digits.begin());
    }
    else if (digits.size() != static_cast<std::size_t>(10))
    {
        throw std::domain_error("invalid phone number");
    }

    if (is_prohibited_first_digit(digits[0]) || is_prohibited_first_digit(digits[3]))
    {
        throw std::domain_error("invalid phone number");
    }

    number_ = digits;
}

std::string phone_number::number() const noexcept
{
    return number_;
}

std::string phone_number::area_code() const noexcept
{
    return number_.substr(0U, 3U);
}

std::string phone_number::pretty() const noexcept
{
    return "(" + number_.substr(0U, 3U) + ") " + number_.substr(3U, 3U) + "-" + number_.substr(6U);
}

}  // namespace phone_number

#include "phone_number.h"

#include <string>
#include <stdexcept>

namespace phone_number {

namespace
{

constexpr bool is_ascii_digit(char ch) noexcept
{
    auto const val {std::char_traits<char>::to_int_type(ch)};
    auto const zero {std::char_traits<char>::to_int_type('0')};
    auto const nine {std::char_traits<char>::to_int_type('9')};
    return ((val >= zero) && (val <= nine));
}

} // unnamed namespace

auto clean(std::string const& number) -> std::string
{
    std::string cleaned_digits {};
    cleaned_digits.reserve(number.length());


    for (std::uint32_t idx {0U}; idx < static_cast<std::uint32_t>(number.length()); ++idx)
    {
        char const ch {number[idx]};
        if (is_ascii_digit(ch) == true)
        {
            cleaned_digits.push_back(ch);
        }
        else
        {
            bool const is_plus_sign {(ch == '+')};
            bool const is_allowed_punctuation {(
                (ch == ' ') ||
                (ch == '.') ||
                (ch == '-') ||
                (ch == '(') ||
                (ch == ')'))};

            if ((is_plus_sign == true) && (idx == 0U))
            {
                continue;
            }

            if (is_allowed_punctuation == true)
            {
                continue;
            }

            throw std::domain_error("invalid character in phone number");
        }
    }

    if (cleaned_digits.size() == 11U)
    {
        if (cleaned_digits[0U] == '1')
        {
            cleaned_digits.erase(0U, 1U);
        }
        else
        {
            throw std::domain_error("11-digit numbers must start with 1");
        }
    }
    else if (cleaned_digits.size() != 10U)
    {
        throw std::domain_error("incorrect number of digits");
    }

    if ((cleaned_digits[0U] == '0') || (cleaned_digits[0U] == '1'))
    {
        throw std::domain_error("area code cannot start with 0 or 1");
    }

    if ((cleaned_digits[3U] == '0') || (cleaned_digits[3U] == '1'))
    {
        throw std::domain_error("exchange code cannot start with 0 or 1");
    }

    return cleaned_digits;
}

phone_number::phone_number(std::string const& numberArg) :
    _number{clean(numberArg)}
{
}

auto phone_number::number() const -> std::string
{
    return _number;
}

auto phone_number::area_code() const -> std::string
{
    return _number.substr(0U, 3U);
}

auto phone_number::pretty() const -> std::string
{
    return "(" + area_code() + ") " + _number.substr(3U, 3U) + "-" + _number.substr(6U, 4U);
}

}  // namespace phone_number

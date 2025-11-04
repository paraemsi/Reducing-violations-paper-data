#include "phone_number.h"

#include <string>
#include <string_view>
#include <stdexcept>

namespace
{
    constexpr const char* DIGIT_CHARS     = "0123456789";
    constexpr const char* VALID_N_CHARS   = "23456789";

    /*  Equality-only test to respect MISRA rule on character numerical value usage. */
    auto is_digit(char ch) -> bool
    {
        return (std::string_view(DIGIT_CHARS).find(ch) != std::string_view::npos);
    }

    /*  First digit of area/exchange code must be 2-9 in NANP. */
    auto is_valid_n_char(char ch) -> bool
    {
        return (std::string_view(VALID_N_CHARS).find(ch) != std::string_view::npos);
    }

    /*  Core sanitising logic shared by the public helpers. */
    auto sanitize(std::string_view input) -> std::string
    {
        std::string digits{};
        digits.reserve(input.size());

        for (char ch : input)
        {
            if (is_digit(ch))
            {
                digits.push_back(ch);
            }
        }

        if (digits.size() == 11U)
        {
            if (digits.front() == '1')
            {
                digits.erase(0U, 1U);
            }
            else
            {
                return std::string("0000000000");
            }
        }

        if (digits.size() != 10U)
        {
            return std::string("0000000000");
        }

        if ((!is_valid_n_char(digits[0U])) || (!is_valid_n_char(digits[3U])))
        {
            return std::string("0000000000");
        }

        return digits;
    }
} // unnamed namespace

namespace phone_number {

phone_number::phone_number(std::string_view input)
    : cleaned_{ sanitize(input) }
{
    if (cleaned_ == "0000000000")
    {
        throw std::domain_error("invalid phone number");
    }
}

auto phone_number::number() const -> std::string
{
    return cleaned_;
}

auto phone_number::area_code() const -> std::string
{
    return cleaned_.substr(0U, 3U);
}

auto phone_number::pretty() const -> std::string
{
    return "(" + cleaned_.substr(0U, 3U) + ") " + cleaned_.substr(3U, 3U) + "-" + cleaned_.substr(6U);
}

}  // namespace phone_number

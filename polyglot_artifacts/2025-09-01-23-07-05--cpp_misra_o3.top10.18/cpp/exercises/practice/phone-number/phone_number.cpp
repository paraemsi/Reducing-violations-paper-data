#include "phone_number.h"

#include <string>
#include <array>
#include <stdexcept>

namespace phone_number {

namespace
{
constexpr const char* invalid_number = "0000000000";

bool is_valid_digit_string(const std::string& digits)
{
    if(digits.length() != static_cast<std::size_t>(10U))
    {
        return false;
    }

    /* area code cannot start with 0 or 1 and exchange code cannot start with 0 or 1 */
    if((digits[0] == '0') || (digits[0] == '1'))
    {
        return false;
    }

    if((digits[3] == '0') || (digits[3] == '1'))
    {
        return false;
    }

    return true;
}
} // unnamed namespace

phone_number::phone_number(std::string_view input)
    : m_number{}
{
    std::string digits {};
    /* helper for digit classification without using <cctype> */
    constexpr auto is_digit_char = [](const char c) noexcept -> bool
    {
        constexpr std::array<char, 10U> digit_chars { '0','1','2','3','4','5','6','7','8','9' };
        for(const char d : digit_chars)
        {
            if(c == d)
            {
                return true;
            }
        }
        return false;
    };

    for(const char ch : input)
    {
        if(is_digit_char(ch))
        {
            digits.push_back(ch);
        }
    }

    if((digits.length() == static_cast<std::size_t>(11U)) && (digits.front() == '1'))
    {
        digits.erase(digits.begin());
    }

    if(is_valid_digit_string(digits))
    {
        m_number = digits;
    }
    else
    {
        throw std::domain_error("invalid phone number");
    }
}

[[nodiscard]] std::string phone_number::number() const
{
    return m_number;
}

[[nodiscard]] std::string phone_number::area_code() const
{
    return m_number.substr(static_cast<std::size_t>(0U), static_cast<std::size_t>(3U));
}

[[nodiscard]] std::string phone_number::pretty() const
{
    const std::string area { area_code() };
    const std::string exchange { m_number.substr(static_cast<std::size_t>(3U), static_cast<std::size_t>(3U)) };
    const std::string subscriber { m_number.substr(static_cast<std::size_t>(6U)) };

    return "(" + area + ") " + exchange + "-" + subscriber;
}

}  // namespace phone_number

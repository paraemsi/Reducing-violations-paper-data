#include "phone_number.h"

#include <locale>
#include <stdexcept>
#include <string>

namespace phone_number {

auto clean(const std::string& number) -> std::string
{
    const auto loc = std::locale{};
    std::string digits{};
    digits.reserve(number.size());

    for (const char ch : number)
    {
        if (std::isdigit(ch, loc) != false)
        {
            digits.push_back(ch);
        }
        else if ((ch == '+') || (ch == '-') || (ch == '(') || (ch == ')') ||
                 (ch == '.') || (ch == ' '))
        {
            /* permitted punctuation – ignore */
        }
        else
        {
            throw std::invalid_argument{"invalid characters in phone number"};
        }
    }

    if (digits.size() == static_cast<std::size_t>(11))
    {
        if (digits[0] == '1')
        {
            digits.erase(static_cast<std::size_t>(0), static_cast<std::size_t>(1));
        }
        else
        {
            throw std::invalid_argument{"11-digit numbers must start with country code 1"};
        }
    }

    if (digits.size() != static_cast<std::size_t>(10))
    {
        throw std::invalid_argument{"incorrect number of digits"};
    }

    if ((digits[0] == '0') || (digits[0] == '1'))
    {
        throw std::invalid_argument{"area code cannot start with 0 or 1"};
    }

    if ((digits[3] == '0') || (digits[3] == '1'))
    {
        throw std::invalid_argument{"exchange code cannot start with 0 or 1"};
    }

    return digits;
}

phone_number::phone_number(const std::string& raw) : number_{ clean(raw) }
{
}

auto phone_number::number() const -> std::string
{
    return number_;
}

auto phone_number::area_code() const -> std::string
{
    return number_.substr(static_cast<std::size_t>(0), static_cast<std::size_t>(3));
}

auto phone_number::pretty() const -> std::string
{
    std::string formatted{"("};
    formatted += area_code();
    formatted += ") ";
    formatted += number_.substr(static_cast<std::size_t>(3), static_cast<std::size_t>(3));
    formatted += '-';
    formatted += number_.substr(static_cast<std::size_t>(6), static_cast<std::size_t>(4));
    return formatted;
}

}  // namespace phone_number

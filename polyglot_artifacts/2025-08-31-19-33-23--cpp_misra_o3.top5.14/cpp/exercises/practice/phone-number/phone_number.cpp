#include "phone_number.h"
#include <string>
#include <string_view>
#include <cstddef>
#include <stdexcept>

namespace phone_number {

namespace {

/* Helper: returns true if the character represents a decimal digit            */
bool is_digit(const char ch) noexcept
{
    constexpr std::string_view digits{"0123456789"};
    return digits.find(ch) != std::string_view::npos;
}

} // unnamed namespace

phone_number::phone_number(const std::string& input)
{
    std::string cleaned{};
    cleaned.reserve(input.size());

    std::size_t pos{0U};

    for (const char c : input)
    {
        if (is_digit(c))
        {
            cleaned.push_back(c);
        }
        else
        {
            /* '+' is permitted only as the very first character.              */
            const bool is_permitted_plus{(c == '+') && (pos == static_cast<std::size_t>(0))};
            const bool is_permitted_punct{(c == ' ') || (c == '(') || (c == ')') ||
                                          (c == '.') || (c == '-')};

            if (!(is_permitted_plus || is_permitted_punct))
            {
                throw std::domain_error("invalid number");
            }
        }
        ++pos;
    }

    if ((cleaned.size() == static_cast<std::size_t>(11)) && (cleaned.front() == '1'))
    {
        cleaned.erase(static_cast<std::size_t>(0), static_cast<std::size_t>(1));
    }

    if (cleaned.size() != static_cast<std::size_t>(10))
    {
        throw std::domain_error("invalid number");
    }

    if ((cleaned[static_cast<std::size_t>(0)] == '0') || (cleaned[static_cast<std::size_t>(0)] == '1'))
    {
        throw std::domain_error("invalid number");
    }

    if ((cleaned[static_cast<std::size_t>(3)] == '0') || (cleaned[static_cast<std::size_t>(3)] == '1'))
    {
        throw std::domain_error("invalid number");
    }

    digits_ = cleaned;
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
    return '(' + digits_.substr(static_cast<std::size_t>(0), static_cast<std::size_t>(3)) + ") " +
           digits_.substr(static_cast<std::size_t>(3), static_cast<std::size_t>(3)) + '-' +
           digits_.substr(static_cast<std::size_t>(6), static_cast<std::size_t>(4));
}

}  // namespace phone_number

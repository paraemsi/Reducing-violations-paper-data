#include "phone_number.h"

#include <algorithm>
#include <locale>
#include <string>
#include <string_view>
#include <stdexcept>

namespace phone_number {

namespace
{
    constexpr std::string_view valid_first_digits{"23456789"};

    // Return true if the character represents a decimal digit.
    inline bool char_is_digit(const char ch)
    {
        /*  Classification helper compliant with MISRA C++.
            Passing the plain character directly is defined behaviour for the
            locale-aware overload of std::isdigit(). */
        return std::isdigit(ch, std::locale{});
    }

    // Return true if the character is an allowed first digit
    // (cannot be 0 or 1) for area/exchange codes.
    inline bool char_is_valid_first(const char ch)
    {
        return (valid_first_digits.find(ch) != std::string_view::npos);
    }
} // unnamed namespace

phone_number::phone_number(const std::string& input)
{
    std::string digits{};
    digits.reserve(input.size());

    /*  Extract decimal digits; reject alphabetic characters outright.        */
    for (const char ch : input)
    {
        if (char_is_digit(ch))
        {
            digits.push_back(ch);
        }
        else
        {
            if (std::isalpha(ch, std::locale{}))
            {
                throw std::domain_error("letters not permitted");
            }
            /*  Ignore all other punctuation / whitespace characters.          */
        }
    }

    /*  Handle optional leading NANP country code '1'.                        */
    if (digits.size() == static_cast<std::size_t>(11U))
    {
        if (digits.front() == '1')
        {
            digits.erase(0U, 1U);
        }
        else
        {
            throw std::domain_error("11 digits must start with 1");
        }
    }
    else if (digits.size() != static_cast<std::size_t>(10U))
    {
        throw std::domain_error("incorrect number of digits");
    }

    /*  Validate area and exchange codes – first digits must be 2-9.          */
    if ((!char_is_valid_first(digits[0])) || (!char_is_valid_first(digits[3])))
    {
        throw std::domain_error("invalid area or exchange code");
    }

    digits_ = digits;
}

std::string phone_number::number() const
{
    return digits_;
}

std::string phone_number::area_code() const
{
    return digits_.substr(0U, 3U);
}

std::string phone_number::pretty() const
{
    const std::string exchange{digits_.substr(3U, 3U)};
    const std::string subscriber{digits_.substr(6U, 4U)};

    std::string result{"("};
    result.append(area_code());
    result.append(") ");
    result.append(exchange);
    result.push_back('-');
    result.append(subscriber);

    return result;
}

}  // namespace phone_number

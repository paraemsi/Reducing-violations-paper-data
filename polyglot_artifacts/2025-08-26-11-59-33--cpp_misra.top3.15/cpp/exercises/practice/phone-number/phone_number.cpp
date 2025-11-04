#include "phone_number.h"
#include <string>
#include <cctype>
#include <stdexcept>

namespace phone_number {

static std::string clean_digits(const std::string& input)
{
    std::string digits;
    for (std::size_t i = 0U; i < input.size(); ++i)
    {
        char ch = input[i];
        if ((ch >= '0') && (ch <= '9'))
        {
            digits += ch;
        }
    }
    if ((digits.size() == 11U) && (digits[0] == '1'))
    {
        digits = digits.substr(1U);
    }
    return digits;
}

phone_number::phone_number(const std::string& input)
{
    digits_ = clean_digits(input);

    // Validate length
    if (digits_.size() != 10U)
    {
        throw std::domain_error("Invalid phone number length");
    }

    // Validate area code and exchange code
    // Area code: digits_[0], digits_[1], digits_[2]
    // Exchange code: digits_[3], digits_[4], digits_[5]
    if ((digits_[0] < '2') || (digits_[0] > '9'))
    {
        throw std::domain_error("Invalid area code");
    }
    if ((digits_[3] < '2') || (digits_[3] > '9'))
    {
        throw std::domain_error("Invalid exchange code");
    }
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
    return "(" + digits_.substr(0U, 3U) + ") " +
           digits_.substr(3U, 3U) + "-" +
           digits_.substr(6U, 4U);
}

}  // namespace phone_number

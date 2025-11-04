#include "phone_number.h"
#include <cctype>
#include <stdexcept>

namespace phone_number {

namespace {
    const std::string INVALID_NUMBER = "0000000000";

    bool is_valid_number(const std::string& digits)
    {
        if (digits.size() != 10)
            return false;

        // Area code cannot start with 0 or 1
        if (digits[0] < '2')
            return false;
        // Exchange code cannot start with 0 or 1
        if (digits[3] < '2')
            return false;

        return true;
    }
}

std::string clean_number(const std::string& input)
{
    std::string digits;
    digits.reserve(input.size());

    for (char ch : input) {
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            digits.push_back(ch);
        } else if (std::isalpha(static_cast<unsigned char>(ch))) {
            throw std::domain_error{"letters not permitted"};
        }
    }

    if (digits.size() == 11 && digits.front() == '1') {
        digits.erase(digits.begin());
    }

    if (!is_valid_number(digits)) {
        throw std::domain_error{"invalid number"};
    }

    return digits;
}

phone_number::phone_number(const std::string& input)
    : digits_{clean_number(input)} {}

std::string phone_number::number() const
{
    return digits_;
}

std::string phone_number::area_code() const
{
    return digits_.substr(0, 3);
}

std::string phone_number::pretty_print() const
{
    return "(" + digits_.substr(0, 3) + ") " + digits_.substr(3, 3) + "-" + digits_.substr(6);
}

// ------------------------------------------------------------------
// Free-function interface required by the public API
// ------------------------------------------------------------------
std::string number(const std::string& input)
{
    return clean_number(input);
}

std::string area_code(const std::string& input)
{
    phone_number pn(input);
    return pn.area_code();
}

std::string pretty_print(const std::string& input)
{
    phone_number pn(input);
    return pn.pretty_print();
}

}  // namespace phone_number

#include "phone_number.h"

#include <cctype>
#include <stdexcept>

namespace phone_number {
namespace {

// Strip all non-digit characters, remove a leading country code (1)
// if present, and return the remaining digits.
std::string clean_digits(const std::string& input)
{
    std::string digits;
    digits.reserve(input.size());

    for (unsigned char ch : input) {
        if (std::isdigit(ch)) {
            digits.push_back(static_cast<char>(ch));
        }
    }

    // Handle an 11-digit number that starts with the NANP country code '1'.
    if (digits.size() == 11 && digits.front() == '1') {
        digits.erase(digits.begin());
    }

    return digits;
}

// Validate that the cleaned string represents a valid NANP phone number.
bool is_valid(const std::string& digits)
{
    // Must be exactly 10 digits.
    if (digits.size() != 10) {
        return false;
    }

    // Area code and exchange code must start with 2-9.
    return (digits[0] >= '2' && digits[0] <= '9') &&
           (digits[3] >= '2' && digits[3] <= '9');
}

// Constant returned when the supplied number is invalid.
const std::string invalid_number = "0000000000";

} // namespace

std::string number(const std::string& input)
{
    const auto digits = clean_digits(input);
    return is_valid(digits) ? digits : invalid_number;
}

std::string area_code(const std::string& input)
{
    return number(input).substr(0, 3);
}

std::string pretty(const std::string& input)
{
    const auto num = number(input);
    return "(" + num.substr(0, 3) + ") " + num.substr(3, 3) + "-" + num.substr(6, 4);
}

// -----------------------------------------------------------------------------
// Object-oriented interface implementation

phone_number::phone_number(const std::string& input)
{
    auto cleaned = clean_digits(input);
    if (!is_valid(cleaned)) {
        throw std::domain_error("invalid phone number");
    }
    digits_ = std::move(cleaned);
}

std::string phone_number::number() const
{
    return digits_;
}

std::string phone_number::area_code() const
{
    return digits_.substr(0, 3);
}

std::string phone_number::pretty() const
{
    return "(" + digits_.substr(0, 3) + ") " + digits_.substr(3, 3) + "-" + digits_.substr(6, 4);
}

}  // namespace phone_number

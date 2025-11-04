#include "phone_number.h"

#include <cstddef>
#include <string>
#include <stdexcept>

namespace phone_number {

namespace {
/* Helper constant containing all decimal digit characters */
constexpr char digit_array[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
const std::string kDigits{digit_array, sizeof(digit_array)};
}  // unnamed namespace

phone_number::phone_number(const std::string& input)
{
    digits_ = clean(input);
    if (!is_valid(digits_)) {
        throw std::domain_error("invalid phone number");
    }
}

std::string phone_number::number() const
{
    return digits_;
}

std::string phone_number::area_code() const
{
    return digits_.substr(static_cast<std::string::size_type>(0), static_cast<std::string::size_type>(3));
}

std::string phone_number::pretty() const
{
    return "(" + area_code() + ") " + digits_.substr(static_cast<std::string::size_type>(3),
                                                     static_cast<std::string::size_type>(3)) +
           "-" + digits_.substr(static_cast<std::string::size_type>(6));
}

std::string phone_number::clean(const std::string& input)
{
    std::string digits;
    digits.reserve(input.size());

    for (char ch : input) {
        if (kDigits.find(ch) != std::string::npos) {
            digits.push_back(ch);
        }
    }

    if ((digits.size() == static_cast<std::string::size_type>(11)) && (digits.front() == '1')) {
        digits.erase(static_cast<std::string::size_type>(0), static_cast<std::string::size_type>(1));
    }


    return digits;
}

bool phone_number::is_valid(const std::string& digits)
{
    if (digits.size() != static_cast<std::string::size_type>(10)) {
        return false;
    }

    if ((digits[0] == '0') || (digits[0] == '1')) {
        return false;
    }

    if ((digits[3] == '0') || (digits[3] == '1')) {
        return false;
    }

    return true;
}

}  // namespace phone_number

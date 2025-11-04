#include "phone_number.h"

#include <cctype>
#include <stdexcept>

namespace phone_number {

namespace {
/* Return a string containing only the decimal digits from the input. */
std::string digits_only(const std::string& input)
{
    std::string out;
    out.reserve(input.size());
    for (char ch : input) {
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            out.push_back(ch);
        }
    }
    return out;
}
} // namespace

std::string number(const std::string& input)
{
    std::string digits = digits_only(input);

    // Handle optional leading country code '1'
    if (digits.size() == 11) {
        if (digits.front() == '1') {
            digits.erase(0, 1);
        } else {
            throw std::domain_error("invalid phone number");
        }
    }

    if (digits.size() != 10) {
        throw std::domain_error("invalid phone number");
    }

    // Validate NANP rules: area and exchange codes cannot start with 0 or 1
    if (digits[0] < '2' || digits[3] < '2') {
        throw std::domain_error("invalid phone number");
    }

    return digits;
}

std::string area_code(const std::string& input)
{
    return number(input).substr(0, 3);
}

std::string pretty(const std::string& input)
{
    const auto num = number(input);
    return "(" + num.substr(0, 3) + ") " + num.substr(3, 3) + "-" +
           num.substr(6, 4);
}

/* ---------- class phone_number implementation --------------------------- */

phone_number::phone_number::phone_number(const std::string& input)
    : digits_(::phone_number::number(input))
{}

std::string phone_number::phone_number::number() const
{
    return digits_;
}

std::string phone_number::phone_number::area_code() const
{
    return digits_.substr(0, 3);
}

std::string phone_number::phone_number::pretty() const
{
    return "(" + digits_.substr(0, 3) + ") " + digits_.substr(3, 3) + "-" +
           digits_.substr(6, 4);
}

}  // namespace phone_number

#include "phone_number.h"

#include <algorithm>
#include <cctype>
#include <iterator>
#include <stdexcept>

namespace phone_number {

// helper: strip everything except digits
static std::string only_digits(const std::string& input)
{
    std::string result;
    std::copy_if(input.begin(), input.end(), std::back_inserter(result),
                 [](unsigned char ch) { return std::isdigit(ch); });
    return result;
}

// static
bool phone_number::valid(const std::string& digits)
{
    if (digits.size() != 10) {
        return false;
    }
    // area code cannot start with 0 or 1
    if (digits[0] < '2' || digits[0] > '9') {
        return false;
    }
    // exchange code cannot start with 0 or 1
    if (digits[3] < '2' || digits[3] > '9') {
        return false;
    }
    return true;
}

phone_number::phone_number(const std::string& input)
{
    std::string raw = only_digits(input);

    // Reject if more than 11 digits
    if (raw.size() > 11) {
        throw std::domain_error("invalid phone number");
    }

    // Optional leading country code '1'
    if (raw.size() == 11) {
        if (raw.front() == '1') {
            raw.erase(raw.begin());
        } else {
            throw std::domain_error("invalid phone number");
        }
    }

    if (!valid(raw)) {
        throw std::domain_error("invalid phone number");
    }

    digits_ = raw;
}

std::string phone_number::number() const
{
    return digits_;
}

std::string phone_number::area_code() const
{
    return digits_.substr(0, 3);
}

phone_number::operator std::string() const
{
    return "(" + area_code() + ") " +
           digits_.substr(3, 3) + "-" +
           digits_.substr(6, 4);
}

}  // namespace phone_number

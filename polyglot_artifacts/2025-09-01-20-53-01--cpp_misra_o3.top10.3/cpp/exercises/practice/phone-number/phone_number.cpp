#include "phone_number.h"

#include <locale>
#include <sstream>
#include <string>

namespace phone_number {

namespace {

constexpr char invalid_number[] = "0000000000";

inline bool is_digit(char ch)
{
    return std::isdigit(ch, std::locale{});
}

bool first_digit_valid(char ch)
{
    static const std::string allowed{"23456789"};
    return (allowed.find(ch) != std::string::npos);
}

std::string sanitize(std::string_view input)
{
    std::string digits{};
    digits.reserve(input.size());

    for (char ch : input) {
        if (is_digit(ch)) {
            digits.push_back(ch);
        }
    }

    if (digits.size() == 11U) {
        if (digits.front() == '1') {
            digits.erase(digits.begin());
        } else {
            return invalid_number;
        }
    }

    if (digits.size() != 10U) {
        return invalid_number;
    }

    if ((!first_digit_valid(digits[0])) || (!first_digit_valid(digits[3]))) {
        return invalid_number;
    }

    return digits;
}

} // namespace

phone_number::phone_number(const std::string& input)
    : cleaned_number_{sanitize(input)}
{
}

std::string phone_number::number() const
{
    return cleaned_number_;
}

std::string phone_number::area_code() const
{
    return cleaned_number_.substr(0U, 3U);
}

std::string phone_number::pretty() const
{
    std::ostringstream oss{};
    oss << '(' << cleaned_number_.substr(0U, 3U) << ") "
        << cleaned_number_.substr(3U, 3U) << '-'
        << cleaned_number_.substr(6U, 4U);
    return oss.str();
}

}  // namespace phone_number

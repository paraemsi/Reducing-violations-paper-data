#include "phone_number.h"

#include <locale>
#include <string_view>
#include <algorithm>
#include <stdexcept>

namespace {


// Convert a digit character to its integer value (0-9)
auto char_to_int(char ch) -> std::int32_t
{
    return (std::char_traits<char>::to_int_type(ch) -
            std::char_traits<char>::to_int_type('0'));
}

} // unnamed namespace

namespace phone_number {

auto phone_number::clean_input(std::string_view input) -> std::string
{
    const std::locale loc{};
    std::string only_digits{};
    only_digits.reserve(input.size());

    for (char c : input) {
        if (std::isdigit(c, loc) != 0) {
            only_digits.push_back(c);
        }
    }

    if (only_digits.size() == static_cast<std::size_t>(11U)) {
        if (only_digits.front() == '1') {
            only_digits.erase(only_digits.begin());
        } else {
            throw std::domain_error("invalid phone number");
        }
    }

    if (!valid_number(only_digits)) {
        throw std::domain_error("invalid phone number");
    }

    return only_digits;
}

auto phone_number::valid_number(const std::string& digits) -> bool
{
    if (digits.size() != static_cast<std::size_t>(10U)) {
        return false;
    }

    const std::int32_t area_first =
        char_to_int(digits[static_cast<std::size_t>(0U)]);
    const std::int32_t exchange_first =
        char_to_int(digits[static_cast<std::size_t>(3U)]);

    if ((area_first < static_cast<std::int32_t>(2)) ||
        (exchange_first < static_cast<std::int32_t>(2))) {
        return false;
    }

    return true;
}

phone_number::phone_number(std::string_view input)
    : digits_{clean_input(input)}
{
}

std::string phone_number::number() const
{
    return digits_;
}

std::string phone_number::area_code() const
{
    return digits_.substr(static_cast<std::size_t>(0U),
                          static_cast<std::size_t>(3U));
}

phone_number::operator std::string() const
{
    std::string formatted{};
    formatted.reserve(static_cast<std::size_t>(14U)); // "(AAA) BBB-CCCC"

    formatted.push_back('(');
    formatted.append(digits_,
                     static_cast<std::size_t>(0U),
                     static_cast<std::size_t>(3U));
    formatted.append(") ");
    formatted.append(digits_,
                     static_cast<std::size_t>(3U),
                     static_cast<std::size_t>(3U));
    formatted.push_back('-');
    formatted.append(digits_,
                     static_cast<std::size_t>(6U),
                     static_cast<std::size_t>(4U));

    return formatted;
}

} // namespace phone_number

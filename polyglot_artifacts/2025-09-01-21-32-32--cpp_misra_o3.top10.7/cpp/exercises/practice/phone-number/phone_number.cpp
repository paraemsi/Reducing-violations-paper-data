#include "phone_number.h"

#include <algorithm>
#include <locale>

namespace phone_number {

namespace {

auto is_digit(char ch) -> bool
{
    /*  Wrapper around std::isdigit from <locale> to comply with the
        MISRA rule forbidding <cctype>.                                                 */
    return (std::isdigit(ch, std::locale{})) != 0;
}

}  // unnamed namespace

phone_number::phone_number(const std::string& input)
{
    std::string cleaned{};
    cleaned.reserve(input.size());

    for (char ch : input) {
        if (is_digit(ch)) {
            cleaned.push_back(ch);
        }
    }

    if ((cleaned.size() == 11U) && (cleaned.front() == '1')) {
        cleaned.erase(0U, 1U);
    }

    if (cleaned.size() != 10U) {
        throw std::domain_error("invalid telephone number length");
    }

    if ((cleaned[0U] == '0') || (cleaned[0U] == '1')) {
        throw std::domain_error("invalid area code");
    }

    if ((cleaned[3U] == '0') || (cleaned[3U] == '1')) {
        throw std::domain_error("invalid exchange code");
    }

    m_digits = cleaned;
}

auto phone_number::number() const -> std::string
{
    return m_digits;
}

auto phone_number::area_code() const -> std::string
{
    return m_digits.substr(0U, 3U);
}

auto phone_number::pretty() const -> std::string
{
    const std::string part1{m_digits.substr(0U, 3U)};
    const std::string part2{m_digits.substr(3U, 3U)};
    const std::string part3{m_digits.substr(6U, 4U)};
    return "(" + part1 + ") " + part2 + "-" + part3;
}

}  // namespace phone_number

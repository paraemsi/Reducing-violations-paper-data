#include "phone_number.h"
#include <cstddef>
#include <stdexcept>

namespace phone_number {

static constexpr std::size_t ten_digits{static_cast<std::size_t>(10U)};
static constexpr std::size_t eleven_digits{static_cast<std::size_t>(11U)};

phone_number::phone_number(const std::string& input)
{
    const std::string digits{"0123456789"};
    std::string extracted{};
    extracted.reserve(input.size());

    for (char c : input) {
        if (digits.find(c) != std::string::npos) {
            extracted.push_back(c);
        }
    }

    /* Handle optional country code */
    if (extracted.size() == eleven_digits) {
        if (extracted.front() == '1') {
            extracted.erase(static_cast<std::size_t>(0U), static_cast<std::size_t>(1U));
        } else {
            throw std::domain_error("11-digit numbers must start with country code 1");
        }
    }

    /* Verify final length */
    if (extracted.size() != ten_digits) {
        throw std::domain_error("invalid number of digits");
    }

    /* Validate NANP rules: area and exchange codes must not start with 0 or 1 */
    if ((extracted.at(static_cast<std::size_t>(0U)) == '0') ||
        (extracted.at(static_cast<std::size_t>(0U)) == '1') ||
        (extracted.at(static_cast<std::size_t>(3U)) == '0') ||
        (extracted.at(static_cast<std::size_t>(3U)) == '1')) {
        throw std::domain_error("invalid area or exchange code");
    }

    clean_number_ = extracted;
}

std::string phone_number::number() const
{
    return clean_number_;
}

std::string phone_number::area_code() const
{
    return clean_number_.substr(static_cast<std::size_t>(0U), static_cast<std::size_t>(3U));
}

std::string phone_number::pretty() const
{
    return "(" + area_code() + ") " +
           clean_number_.substr(static_cast<std::size_t>(3U), static_cast<std::size_t>(3U)) +
           "-" +
           clean_number_.substr(static_cast<std::size_t>(6U));
}

}  // namespace phone_number

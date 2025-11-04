#include "phone_number.h"

#include <locale>
#include <string>
#include <cstddef>   // for std::size_t
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& input)
{
    const std::locale loc {};

    std::string cleaned {};
    cleaned.reserve(input.size());

    for (const char ch : input) {
        if (std::isdigit(ch, loc) != 0) {
            cleaned.push_back(ch);
        }
    }

    if (cleaned.size() == static_cast<std::string::size_type>(11U)) {
        if (cleaned[0] == '1') {
            cleaned.erase(0, static_cast<std::string::size_type>(1U));
        } else {
            cleaned.clear();
        }
    }

    if (cleaned.size() != static_cast<std::string::size_type>(10U)) {
        cleaned.clear();
    }

    if ((!cleaned.empty()) && ((cleaned[0] == '0') || (cleaned[0] == '1'))) {
        cleaned.clear();
    }

    if ((!cleaned.empty()) && ((cleaned[3] == '0') || (cleaned[3] == '1'))) {
        cleaned.clear();
    }

    if (cleaned.empty()) {
        throw std::domain_error("invalid phone number");
    }

    digits_ = cleaned;
}

std::string phone_number::number() const
{
    return digits_;
}

std::string phone_number::area_code() const
{
    return digits_.substr(0, static_cast<std::string::size_type>(3U));
}

std::string phone_number::pretty() const
{
    return "(" + area_code() + ") "
           + digits_.substr(static_cast<std::string::size_type>(3U),
                             static_cast<std::string::size_type>(3U))
           + "-"
           + digits_.substr(static_cast<std::string::size_type>(6U),
                             static_cast<std::string::size_type>(4U));
}

}  // namespace phone_number

#include "phone_number.h"

#include <string>
#include <cstddef>
#include <stdexcept>

namespace phone_number {

namespace {
    // Check if a character is one of '0'..'9' without relying on numeric value of the character.
    bool is_digit_char(const char ch) {
        static const std::string digits{"0123456789"};
        return (digits.find(ch) != std::string::npos);
    }
}  // namespace

phone_number::phone_number::phone_number(const std::string& input)
    : digits_{} {
    std::string cleaned{};
    cleaned.reserve(input.size());

    static const std::string allowed_symbols{" .()-+"};

    for (const char ch : input) {
        if (is_digit_char(ch)) {
            cleaned.push_back(ch);
        } else if ((allowed_symbols.find(ch) != std::string::npos)) {
            {
                // allowed non-digit symbol, ignore
            }
        } else {
            throw std::domain_error("invalid character in phone number");
        }
    }

    if (cleaned.size() > static_cast<std::size_t>(11)) {
        throw std::domain_error("too many digits");
    }

    if (cleaned.size() == static_cast<std::size_t>(11)) {
        if (cleaned.front() == '1') {
            cleaned.erase(static_cast<std::size_t>(0), static_cast<std::size_t>(1));
        } else {
            throw std::domain_error("11 digits must start with country code 1");
        }
    }

    if (cleaned.size() != static_cast<std::size_t>(10)) {
        throw std::domain_error("incorrect number of digits");
    }

    if ((cleaned[static_cast<std::size_t>(0)] == '0') || (cleaned[static_cast<std::size_t>(0)] == '1')
        || (cleaned[static_cast<std::size_t>(3)] == '0') || (cleaned[static_cast<std::size_t>(3)] == '1')) {
        throw std::domain_error("area or exchange code cannot start with 0 or 1");
    }

    digits_ = cleaned;
}

std::string phone_number::phone_number::number() const {
    return digits_;
}

std::string phone_number::phone_number::area_code() const {
    return digits_.substr(static_cast<std::size_t>(0), static_cast<std::size_t>(3));
}

std::string phone_number::phone_number::pretty() const {
    const std::string ac{area_code()};
    const std::string exchange{digits_.substr(static_cast<std::size_t>(3), static_cast<std::size_t>(3))};
    const std::string subscriber{digits_.substr(static_cast<std::size_t>(6), static_cast<std::size_t>(4))};
    return (((("(" + ac) + ") ") + exchange) + "-") + subscriber;
}

}  // namespace phone_number

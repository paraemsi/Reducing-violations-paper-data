#include "phone_number.h"

#include <string>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace phone_number {

namespace {
    inline bool invalid_area_or_exchange(const std::string& digits) {
        if ((digits.size() < static_cast<std::size_t>(7))) {
            return true;
        } else {
            if ((digits[0] == '0') || (digits[0] == '1')) {
                return true;
            } else {
                if ((digits[3] == '0') || (digits[3] == '1')) {
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
}

phone_number::phone_number(const std::string& input)
    : cleaned_()
{
    std::string digits;
    digits.reserve(input.size());

    bool has_alpha = false;
    bool invalid_punct = false;

    for (const char ch : input) {
        if ((std::isdigit(static_cast<unsigned char>(ch)) != 0)) {
            digits.push_back(ch);
        } else {
            if ((std::isalpha(static_cast<unsigned char>(ch)) != 0)) {
                has_alpha = true;
            } else {
                if ((std::isspace(static_cast<unsigned char>(ch)) != 0)) {
                    // ignore whitespace
                } else {
                    if ((ch == '(') || (ch == ')') || (ch == '.') || (ch == '-') || (ch == '+')) {
                        // allowed punctuation, ignore
                    } else {
                        invalid_punct = true;
                    }
                }
            }
        }
    }

    const std::size_t ten = static_cast<std::size_t>(10);
    const std::size_t eleven = static_cast<std::size_t>(11);

    if ((has_alpha) || (invalid_punct)) {
        throw std::domain_error("invalid characters in phone number");
    } else {
        // continue
    }

    if ((digits.size() == eleven) && (digits.front() == '1')) {
        digits.erase(static_cast<std::size_t>(0), static_cast<std::size_t>(1));
    } else {
        if ((digits.size() == eleven) && (digits.front() != '1')) {
            throw std::domain_error("invalid country code");
        } else {
            // continue
        }
    }

    if (digits.size() != ten) {
        throw std::domain_error("invalid number of digits");
    } else {
        // continue
    }

    if (invalid_area_or_exchange(digits)) {
        throw std::domain_error("invalid area or exchange code");
    } else {
        cleaned_ = digits;
    }
}

std::string phone_number::number() const {
    return cleaned_;
}

std::string phone_number::area_code() const {
    return cleaned_.substr(static_cast<std::size_t>(0), static_cast<std::size_t>(3));
}

std::string phone_number::to_string() const {
    const std::string ac = area_code();
    const std::string exch = cleaned_.substr(static_cast<std::size_t>(3), static_cast<std::size_t>(3));
    const std::string sub = cleaned_.substr(static_cast<std::size_t>(6), static_cast<std::size_t>(4));

    std::string repr;
    repr.reserve(static_cast<std::size_t>(14));
    repr.push_back('(');
    repr.append(ac);
    repr.append(") ");
    repr.append(exch);
    repr.push_back('-');
    repr.append(sub);

    return repr;
}

}  // namespace phone_number

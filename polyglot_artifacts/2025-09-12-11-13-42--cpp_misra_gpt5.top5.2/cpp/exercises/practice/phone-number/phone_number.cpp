#include "phone_number.h"

#include <cctype>
#include <string>
#include <stdexcept>

namespace phone_number {

namespace {
    bool has_alpha_char(const std::string& s)
    {
        for (const char ch : s) {
            if ((std::isalpha(static_cast<unsigned char>(ch)) != 0)) {
                return true;
            }
        }
        return false;
    }

    std::string only_digits(const std::string& s)
    {
        std::string out;
        out.reserve(s.size());
        for (const char ch : s) {
            if ((std::isdigit(static_cast<unsigned char>(ch)) != 0)) {
                out.push_back(ch);
            }
        }
        return out;
    }
}  // namespace

phone_number::phone_number(const std::string& input) : digits_()
{
    bool invalid = false;

    if (has_alpha_char(input)) {
        invalid = true;
    }

    std::string digits = only_digits(input);

    if (!invalid) {
        if (digits.size() == std::size_t{11U}) {
            if (digits.front() == '1') {
                digits.erase(std::size_t{0U}, std::size_t{1U});
            } else {
                invalid = true;
            }
        }

        if (digits.size() != std::size_t{10U}) {
            invalid = true;
        }

        if (!invalid) {
            const char a0 = digits[0];
            const char e0 = digits[3];
            if ((a0 == '0') || (a0 == '1') || (e0 == '0') || (e0 == '1')) {
                invalid = true;
            }
        }
    }

    if (invalid) {
        throw std::domain_error("invalid phone number");
    } else {
        digits_ = digits;
    }
}

std::string phone_number::number() const
{
    return digits_;
}

std::string phone_number::area_code() const
{
    return digits_.substr(std::size_t{0U}, std::size_t{3U});
}

std::string phone_number::pretty() const
{
    const std::string area = digits_.substr(std::size_t{0U}, std::size_t{3U});
    const std::string exch = digits_.substr(std::size_t{3U}, std::size_t{3U});
    const std::string subs = digits_.substr(std::size_t{6U}, std::size_t{4U});

    std::string out = std::string("(");
    out += area;
    out += std::string(") ");
    out += exch;
    out += std::string("-");
    out += subs;
    return out;
}

}  // namespace phone_number

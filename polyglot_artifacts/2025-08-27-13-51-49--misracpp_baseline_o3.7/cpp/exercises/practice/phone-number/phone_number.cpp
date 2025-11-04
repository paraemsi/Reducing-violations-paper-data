#include "phone_number.h"

#include <cctype>
#include <stdexcept>


namespace {
    // Helper: strip non-digit chars and validate length / codes.
    std::string clean(const std::string& input) {
        std::string digits;
        digits.reserve(input.size());

        for (char ch : input) {
            if (std::isdigit(static_cast<unsigned char>(ch))) {
                digits.push_back(ch);
            }
        }

        // Handle optional leading country code '1'
        if (digits.size() == 11 && digits.front() == '1') {
            digits.erase(digits.begin());
        }

        if (digits.size() != 10) {
            throw std::domain_error("invalid number length");
        }

        // Area code and exchange code first digit must be 2-9
        if (digits[0] < '2' || digits[0] > '9') {
            throw std::domain_error("invalid area code");
        }
        if (digits[3] < '2' || digits[3] > '9') {
            throw std::domain_error("invalid exchange code");
        }

        return digits;
    }
} // namespace

namespace phone_number {

phone_number::phone_number(const std::string& input)
    : digits_(clean(input)) {}

std::string phone_number::number() const {
    return digits_;
}

std::string phone_number::area_code() const {
    return digits_.substr(0, 3);
}

std::string phone_number::pretty() const {
    return "(" + digits_.substr(0, 3) + ") "
         + digits_.substr(3, 3) + "-"
         + digits_.substr(6);
}

} // namespace phone_number


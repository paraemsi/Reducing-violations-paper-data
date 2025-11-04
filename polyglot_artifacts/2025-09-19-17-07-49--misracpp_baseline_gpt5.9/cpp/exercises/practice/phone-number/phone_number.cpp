#include "phone_number.h"

#include <cctype>
#include <string>
#include <stdexcept>

namespace phone_number {

namespace {
    std::string digits_only(const std::string& s) {
        std::string out;
        out.reserve(s.size());
        for (unsigned char ch : s) {
            if (std::isdigit(ch)) {
                out.push_back(static_cast<char>(ch));
            }
        }
        return out;
    }

    std::string normalize(const std::string& input) {
        std::string digits = digits_only(input);

        // Handle NANP country code
        if (digits.size() == 11) {
            if (digits.front() == '1') {
                digits.erase(digits.begin());
            } else {
                throw std::domain_error("Invalid country code");
            }
        }

        if (digits.size() != 10) {
            throw std::domain_error("Invalid NANP phone number length");
        }

        // Validate NANP NXX NXX-XXXX rules: area and exchange codes cannot start with 0 or 1
        if (digits[0] < '2' || digits[0] > '9') {
            throw std::domain_error("Invalid area code");
        }
        if (digits[3] < '2' || digits[3] > '9') {
            throw std::domain_error("Invalid exchange code");
        }

        return digits;
    }
}  // namespace

std::string clean(const std::string& input) {
    return normalize(input);
}

phone_number::phone_number(const std::string& input)
    : digits_(normalize(input)) {}

const std::string& phone_number::number() const {
    return digits_;
}

std::string phone_number::area_code() const {
    return digits_.substr(0, 3);
}

std::string phone_number::to_string() const {
    return "(" + digits_.substr(0, 3) + ") " + digits_.substr(3, 3) + "-" + digits_.substr(6, 4);
}

}  // namespace phone_number

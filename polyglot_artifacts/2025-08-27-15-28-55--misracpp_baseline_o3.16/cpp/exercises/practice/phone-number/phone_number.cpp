#include "phone_number.h"
#include <algorithm>
#include <cctype>
#include <stdexcept>

namespace phone_number {

    std::string clean(const std::string& input) {
        std::string digits;
        digits.reserve(input.size());

        const std::string allowed_punct{"()+-. "};

        // Collect digits and validate characters
        for (char ch : input) {
            unsigned char uch = static_cast<unsigned char>(ch);

            if (std::isdigit(uch)) {
                digits.push_back(ch);
            } else if (std::isalpha(uch)) {
                throw std::domain_error("letters not permitted");
            } else if (std::isspace(uch)) {
                continue;  // ignore whitespace
            } else if (std::ispunct(uch)) {
                if (allowed_punct.find(ch) == std::string::npos) {
                    throw std::domain_error("punctuations not permitted");
                }
            } else {
                throw std::domain_error("punctuations not permitted");
            }
        }

        // Validate digit count and optional country code
        if (digits.size() < 10) {
            throw std::domain_error("incorrect number of digits");
        }
        if (digits.size() > 11) {
            throw std::domain_error("more than 11 digits");
        }
        if (digits.size() == 11) {
            if (digits.front() != '1') {
                throw std::domain_error("11 digits must start with 1");
            }
            digits.erase(digits.begin());  // strip country code
        }

        // Area code checks
        if (digits[0] == '0') {
            throw std::domain_error("area code cannot start with zero");
        }
        if (digits[0] == '1') {
            throw std::domain_error("area code cannot start with one");
        }

        // Exchange code checks
        if (digits[3] == '0') {
            throw std::domain_error("exchange code cannot start with zero");
        }
        if (digits[3] == '1') {
            throw std::domain_error("exchange code cannot start with one");
        }

        return digits;
    }

}  // namespace phone_number

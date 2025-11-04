#include "phone_number.h"

#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>

namespace phone_number {

phone_number::phone_number(const std::string& number) {
    std::string cleaned;
    for (char c : number) {
        if (std::isdigit(c)) {
            cleaned += c;
        }
    }
    if (cleaned.size() == 11 && cleaned[0] == '1') {
        cleaned = cleaned.substr(1);
    }
    if (cleaned.size() != 10) {
        throw std::invalid_argument("Invalid phone number");
    }
    // Validate area code and exchange code
    if (cleaned[0] == '0' || cleaned[0] == '1' ||
        cleaned[3] == '0' || cleaned[3] == '1') {
        throw std::invalid_argument("Invalid phone number");
    }
    this->cleaned = cleaned;
}

std::string phone_number::number() const {
    return cleaned;
}

}  // namespace phone_number

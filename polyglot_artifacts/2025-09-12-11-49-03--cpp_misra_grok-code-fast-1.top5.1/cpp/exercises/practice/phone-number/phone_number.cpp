#include "phone_number.h"

#include <cctype>
#include <stdexcept>
#include <string>

namespace phone_number {

phone_number::phone_number(const std::string& number) {
    std::string result;
    for (char c : number) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            {
                result += c;
            }
        }
    }
    if ((result.length() == 11) && (result[0] == '1')) {
        {
            result = result.substr(1);
        }
    }
    if (result.length() != 10) {
        {
            throw std::domain_error("invalid phone number");
        }
    }
    if ((result[0] < '2') || (result[0] > '9')) {
        {
            throw std::domain_error("invalid phone number");
        }
    }
    if ((result[3] < '2') || (result[3] > '9')) {
        {
            throw std::domain_error("invalid phone number");
        }
    }
    cleaned_number_ = result;
}

std::string phone_number::number() const {
    return cleaned_number_;
}

}  // namespace phone_number

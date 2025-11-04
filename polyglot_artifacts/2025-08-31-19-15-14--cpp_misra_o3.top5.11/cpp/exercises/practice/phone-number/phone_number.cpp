#include "phone_number.h"
#include <cstddef>
#include <stdexcept>
#include <string>

namespace phone_number {

    [[nodiscard]] auto clean(const std::string& number) -> std::string
    {
        static const std::string allowed_digits{"0123456789"};
        static const std::string allowed_punct{" +-.()"}; /* space, plus, dash, dot, parentheses */

        std::string digits_only{};
        digits_only.reserve(number.size());

        for (char ch : number)
        {
            if (allowed_digits.find(ch) != std::string::npos)
            {
                digits_only.push_back(ch);
            }
            else if (allowed_punct.find(ch) != std::string::npos)
            {
                /* permitted punctuation – ignore */
            }
            else
            {
                throw std::domain_error("invalid character");
            }
        }

        if ((digits_only.size() == static_cast<std::size_t>(11U)) && (digits_only[0] == '1'))
        {
            digits_only.erase(0, static_cast<std::string::size_type>(1U));
        }
        else if (digits_only.size() != static_cast<std::size_t>(10U))
        {
            throw std::domain_error("incorrect number of digits");
        }

        if ((digits_only[0] == '0') || (digits_only[0] == '1'))
        {
            throw std::domain_error("area code starts with invalid digit");
        }

        if ((digits_only[3] == '0') || (digits_only[3] == '1'))
        {
            throw std::domain_error("exchange code starts with invalid digit");
        }

        return digits_only;
    }

    phone_number::phone_number(const std::string& raw)
        : digits_{clean(raw)}
    {
    }

    auto phone_number::number() const -> std::string
    {
        return digits_;
    }

    auto phone_number::area_code() const -> std::string
    {
        return digits_.substr(0, static_cast<std::string::size_type>(3U));
    }

    auto phone_number::pretty() const -> std::string
    {
        return "(" + area_code() + ") " +
               digits_.substr(static_cast<std::string::size_type>(3U), static_cast<std::string::size_type>(3U)) +
               "-" +
               digits_.substr(static_cast<std::string::size_type>(6U));
    }

}  // namespace phone_number

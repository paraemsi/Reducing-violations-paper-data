#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

    // Return the cleaned 10-digit NANP phone number or throw
    // std::domain_error if the supplied string is invalid.
    std::string clean(const std::string& input);

    // Public interface expected by the tests -------------------------------
    class phone_number {
    public:
        explicit phone_number(const std::string& input)
            : digits_{clean(input)} {}

        std::string number() const { return digits_; }

        std::string area_code() const { return digits_.substr(0, 3); }

        std::string pretty() const {
            return "(" + area_code() + ") " +
                   digits_.substr(3, 3) + "-" +
                   digits_.substr(6);
        }

    private:
        std::string digits_;
    };
    // ----------------------------------------------------------------------

}  // namespace phone_number

#endif // PHONE_NUMBER_H

#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

/**
 * @brief Clean up a user-entered NANP telephone number.
 *
 * Removes all punctuation and optional country code (1 or +1) and validates
 * the number according to the North-American Numbering Plan rules.
 *
 * @param input  Raw user input containing a telephone number.
 * @return std::string 10-digit cleaned telephone number.
 *
 * @throws std::invalid_argument if the input cannot be converted to a valid
 *         NANP telephone number.
 */
auto clean(const std::string& input) -> std::string;

/**
 * @brief Class wrapper representing a cleaned NANP phone number.
 *
 * Constructs a validated 10-digit phone number and exposes helpers to
 * retrieve the raw digits, the area-code, and a formatted representation.
 *
 * All validation rules are identical to the standalone clean() helper.  Any
 * violation results in a std::invalid_argument exception from the ctor.
 */
class phone_number
{
public:
    explicit phone_number(const std::string& input);

    auto number() const -> std::string;
    auto area_code() const -> std::string;
    auto pretty() const -> std::string;

private:
    std::string digits_;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

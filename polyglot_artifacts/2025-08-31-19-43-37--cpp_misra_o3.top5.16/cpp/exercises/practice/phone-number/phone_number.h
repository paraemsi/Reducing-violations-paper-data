#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <stdexcept>

namespace phone_number {

/**
 * @brief Clean up user-entered phone numbers, returning a 10-digit
 *        string conforming to the North American Numbering Plan.
 *
 * Any punctuation is removed.  A leading country code ‘1’ is
 * stripped if the phone number then contains exactly ten digits.
 *
 * @param input Arbitrary user-entered phone number text.
 * @return A 10-digit number string suitable for SMS routing.
 */
auto clean(const std::string& input) -> std::string;

/*----------------------------------------------------------------------------*/
/*  A convenient wrapper class expected by the unit-tests                     */
/*----------------------------------------------------------------------------*/
class phone_number
{
public:
    explicit phone_number(const std::string& input);

    [[nodiscard]] auto number() const -> std::string;
    [[nodiscard]] auto area_code() const -> std::string;
    [[nodiscard]] auto pretty() const -> std::string;

private:
    std::string digits_;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

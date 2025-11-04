#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

/**
 * @brief Clean up a user-entered NANP telephone number.
 *
 * Strips punctuation, removes a leading country code (1),
 * and validates that the resulting string contains exactly
 * ten digits with a valid area and exchange code.
 *
 * @param raw User-supplied phone number.
 * @return Ten-digit phone number suitable for SMS.
 *
 * @throws std::domain_error If the input is not a valid NANP number.
 */
class phone_number
{
public:
    explicit phone_number(const std::string& raw);

    auto number() const -> std::string;
    auto area_code() const -> std::string;
    auto pretty() const -> std::string;

private:
    std::string digits_;
};

/* Utility function retained for stand-alone use */
auto clean(const std::string& raw) -> std::string;

}  // namespace phone_number

#endif // PHONE_NUMBER_H

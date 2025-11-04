#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

/*
 * Clean up user-entered NANP telephone numbers.
 *
 * Throws std::invalid_argument if the supplied string does not yield a
 * valid 10-digit NANP number after normalisation.
 *
 * The returned string always holds exactly ten digits ready for SMS use.
 */
std::string clean(const std::string& input);

/*----------------------------------------------------------------------------*/
/*  Class representing a validated NANP telephone number                      */
/*----------------------------------------------------------------------------*/
class phone_number
{
public:
    explicit phone_number(const std::string& input);

    [[nodiscard]] std::string number() const;
    [[nodiscard]] std::string area_code() const;
    [[nodiscard]] std::string pretty() const;

private:
    std::string digits_;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

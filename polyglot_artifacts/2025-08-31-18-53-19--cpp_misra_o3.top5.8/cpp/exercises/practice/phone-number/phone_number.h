#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

/*  An immutable representation of a cleaned NANP phone number.
 *  The constructor validates and normalises the supplied input and
 *  throws std::invalid_argument if the data are not a valid NANP number.
 */
class phone_number
{
public:
    explicit phone_number(const std::string& input);

    /* Return the 10-digit cleaned phone number. */
    auto number() const -> std::string;

    /* Return the 3-digit area code portion of the number. */
    auto area_code() const -> std::string;

    /* Return the number formatted as "(XXX) XXX-XXXX". */
    auto pretty() const -> std::string;

private:
    std::string digits_;   /* exactly 10 numeric characters */
};

/*  Clean a user-entered NANP phone number and return the 10-digit
 *  digits-only string.  Throws std::invalid_argument if the supplied
 *  input does not represent a valid NANP phone number.
 */
auto clean(const std::string& input) -> std::string;

}  // namespace phone_number

#endif // PHONE_NUMBER_H

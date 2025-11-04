#ifndef EXERCISM_PHONE_NUMBER_H
#define EXERCISM_PHONE_NUMBER_H

#include <string>

namespace phone_number {

/* Class wrapper used by the tests */
class phone_number {
public:
    explicit phone_number(const std::string& input);

    /* Return the 10-digit cleaned number. */
    std::string number() const;

    /* Return the 3-digit area code. */
    std::string area_code() const;

    /* Return the formatted representation “(XXX) XXX-XXXX”. */
    std::string pretty() const;

private:
    std::string digits_;
};

std::string number(const std::string& input);
std::string area_code(const std::string& input);
std::string pretty(const std::string& input);

}  // namespace phone_number

#endif // EXERCISM_PHONE_NUMBER_H

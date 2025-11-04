#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

#if (__cplusplus >= 201703L)
#  define PN_NODISCARD [[nodiscard]]
#else
#  define PN_NODISCARD
#endif

namespace phone_number {

/*  Class that represents and validates a NANP phone number. */
class phone_number
{
public:
    explicit phone_number(const std::string& input);

    PN_NODISCARD auto number() const -> std::string;
    PN_NODISCARD auto area_code() const -> std::string;
    PN_NODISCARD auto pretty() const -> std::string;

private:
    std::string digits_;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

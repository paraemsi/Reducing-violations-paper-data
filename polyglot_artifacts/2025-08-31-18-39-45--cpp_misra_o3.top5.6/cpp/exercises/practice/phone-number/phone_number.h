#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

/*  Return the cleaned 10-digit phone number.
 *  If the supplied input is invalid according to NANP rules,
 *  the implementation returns "0000000000".
 */
auto number(const std::string &input) -> std::string;

/*  Return the area-code (first three digits) of the cleaned number.
 *  If the supplied input is invalid, "000" is returned.
 */
auto area_code(const std::string &input) -> std::string;

/*  Return the cleaned number formatted as "(XXX) XXX-XXXX".
 *  For invalid input the string "(000) 000-0000" is returned.
 */
auto pretty_print(const std::string &input) -> std::string;

/*---------------------------------------------------------------------------*/
/*  Class-based interface required by the unit test suite.                   */
/*---------------------------------------------------------------------------*/
class phone_number {
public:
    explicit phone_number(const std::string &input);

    auto number() const -> std::string;
    auto area_code() const -> std::string;
    auto pretty_print() const -> std::string;

    /*  Some test suites use the shorter name `pretty()`.               */
    auto pretty() const -> std::string
    {
        return pretty_print();
    }

private:
    std::string m_digits;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

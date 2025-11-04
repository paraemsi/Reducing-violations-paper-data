#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

auto clean(const std::string& input) -> std::string;

/*  A small wrapper class providing the interface expected by the
 *  unit-tests.  Validation and digit-extraction are delegated to the
 *  clean() utility implemented in phone_number.cpp.
 */
class phone_number
{
public:
    explicit phone_number(const std::string& input);

    [[nodiscard]] auto number() const -> std::string;
    [[nodiscard]] auto area_code() const -> std::string;
    [[nodiscard]] auto pretty() const -> std::string;

private:
    std::string m_number;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <stdexcept>

namespace phone_number {

class phone_number {
public:
    explicit phone_number(std::string const& input);
    std::string number() const;
    std::string area_code() const;
    std::string pretty() const;
private:
    std::string digits_;
};

std::string clean(std::string const& input);

}  // namespace phone_number

#endif // PHONE_NUMBER_H

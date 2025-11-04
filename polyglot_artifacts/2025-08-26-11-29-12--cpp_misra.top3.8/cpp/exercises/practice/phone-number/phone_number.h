#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <cstdint>

namespace phone_number {

typedef std::string phone_string_t;

class phone_number
{
public:
    explicit phone_number(std::string const& input);

    std::string number() const;
    std::string area_code() const;
    std::string pretty() const;

private:
    std::string number_;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

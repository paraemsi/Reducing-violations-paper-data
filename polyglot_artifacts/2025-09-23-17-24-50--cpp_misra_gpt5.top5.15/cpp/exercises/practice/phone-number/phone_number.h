#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H
#include <string>

namespace phone_number {

class phone_number
{
public:
    explicit phone_number(std::string const& input);
    auto number() const noexcept -> std::string;

private:
    std::string digits_;
};


auto number(std::string const& input) -> std::string;

}  // namespace phone_number

#endif // PHONE_NUMBER_H

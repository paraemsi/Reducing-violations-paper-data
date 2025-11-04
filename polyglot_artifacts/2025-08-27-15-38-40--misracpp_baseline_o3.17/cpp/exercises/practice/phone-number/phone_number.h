#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {
    // Object-oriented wrapper expected by the tests
    class phone_number {
    public:
        explicit phone_number(const std::string& input);

        std::string number() const;
        std::string area_code() const;
        std::string pretty() const;

    private:
        std::string digits_;
    };
}  // namespace phone_number

#endif // PHONE_NUMBER_H

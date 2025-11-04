#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H
#include <string>
#include <cstddef>

namespace phone_number {

    [[nodiscard]] auto clean(const std::string& number) -> std::string;

    class phone_number final
    {
    public:
        explicit phone_number(const std::string& raw);

        [[nodiscard]] auto number() const -> std::string;
        [[nodiscard]] auto area_code() const -> std::string;
        [[nodiscard]] auto pretty() const -> std::string;

    private:
        std::string digits_;
    };

}  // namespace phone_number

#endif // PHONE_NUMBER_H

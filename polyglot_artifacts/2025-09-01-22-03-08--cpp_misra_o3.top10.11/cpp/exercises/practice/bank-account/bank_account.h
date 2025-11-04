#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

class Bankaccount {
public:
    using int_type = std::int32_t;

    Bankaccount() noexcept;

    void open();
    void close();
    void deposit(int_type amount);
    void withdraw(int_type amount);
    [[nodiscard]] int_type balance() const;

private:
    mutable std::mutex m_;
    int_type balance_;
    bool is_open_;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

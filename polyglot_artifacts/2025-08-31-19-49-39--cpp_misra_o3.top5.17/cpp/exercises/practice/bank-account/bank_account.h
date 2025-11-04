#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>
#include <stdexcept>

namespace Bankaccount {

class Bankaccount
{
public:
    using money_t = std::int32_t;

    Bankaccount() noexcept;

    void open();
    void close();
    void deposit(money_t amount);
    void withdraw(money_t amount);
    [[nodiscard]] money_t balance() const;

private:
    mutable std::mutex mtx_;
    bool               is_open_{false};
    money_t            balance_{static_cast<money_t>(0)};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

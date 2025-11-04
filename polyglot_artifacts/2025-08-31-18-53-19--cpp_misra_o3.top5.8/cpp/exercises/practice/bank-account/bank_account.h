#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

using amount_t = std::int64_t;

class Bankaccount
{
public:
    Bankaccount() noexcept;

    void open();
    void close();
    void deposit(amount_t amount);
    void withdraw(amount_t amount);
    [[nodiscard]] amount_t balance() const;

private:
    mutable std::mutex m_mutex;
    bool m_open;
    amount_t m_balance;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

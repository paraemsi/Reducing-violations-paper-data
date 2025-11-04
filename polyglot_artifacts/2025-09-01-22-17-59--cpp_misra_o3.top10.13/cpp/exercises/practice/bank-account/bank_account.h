#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

using money_t = std::int64_t;  // fixed-width signed integral type for money

class Bankaccount
{
public:
    Bankaccount() noexcept;

    void open();
    void close();

    void deposit(const money_t amount);
    void withdraw(const money_t amount);

    money_t balance() const;

    Bankaccount(const Bankaccount&) = delete;
    Bankaccount& operator=(const Bankaccount&) = delete;

private:
    mutable std::mutex m_mutex;
    bool m_open;
    money_t m_balance;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

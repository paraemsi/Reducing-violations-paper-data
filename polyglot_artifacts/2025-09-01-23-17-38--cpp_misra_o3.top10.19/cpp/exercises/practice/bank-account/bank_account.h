#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

// Alias representing a monetary amount.
using Money = std::int64_t;

class Bankaccount {
public:
    Bankaccount();

    void open();
    void close();
    Money balance() const;
    void deposit(Money amount);
    void withdraw(Money amount);

private:
    mutable std::mutex m_mutex {};
    Money              m_balance {static_cast<Money>(0)};
    bool               m_isOpen {false};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

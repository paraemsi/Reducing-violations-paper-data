#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <cstdint>

namespace Bankaccount {

// Define a type alias for the balance to comply with MISRA rules
using balance_t = std::int64_t;

class Bankaccount {
private:
    balance_t m_balance;
    bool m_is_closed;
    mutable std::mutex m_mtx;
    
public:
    Bankaccount();
    void open();
    void deposit(balance_t amount);
    void withdraw(balance_t amount);
    balance_t balance() const;
    void close();
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

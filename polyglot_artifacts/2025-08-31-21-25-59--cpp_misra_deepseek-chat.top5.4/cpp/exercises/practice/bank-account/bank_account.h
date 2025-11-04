#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <cstdint>

namespace Bankaccount {

// Define an alias for the balance type
using BalanceType = std::int64_t;

class Bankaccount {
private:
    BalanceType m_balance;
    bool m_is_open;
    mutable std::mutex m_mtx;
    
public:
    Bankaccount();
    void open();
    void deposit(BalanceType amount);
    void withdraw(BalanceType amount);
    BalanceType balance() const;
    void close();
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

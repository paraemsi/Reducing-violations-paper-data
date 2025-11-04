#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

// Define a type alias for the balance type to comply with MISRA rules
using BankAccountBalanceType = std::int64_t;

class Bankaccount {
private:
    BankAccountBalanceType m_balance;
    bool m_is_open;
    mutable std::mutex m_mtx;
    
public:
    Bankaccount();
    void open();
    void close();
    void deposit(BankAccountBalanceType amount);
    void withdraw(BankAccountBalanceType amount);
    BankAccountBalanceType balance() const;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

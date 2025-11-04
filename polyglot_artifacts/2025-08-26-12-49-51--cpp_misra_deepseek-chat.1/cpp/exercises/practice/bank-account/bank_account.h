#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <cstdint>

namespace Bankaccount {

// Define an alias for the integer type to use
using AccountValue = std::int64_t;

class Bankaccount {
private:
    AccountValue m_balance;
    bool m_is_open;
    mutable std::mutex m_mtx;
    
public:
    Bankaccount();
    void open();
    void deposit(AccountValue amount);
    void withdraw(AccountValue amount);
    AccountValue balance() const;
    void close();
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

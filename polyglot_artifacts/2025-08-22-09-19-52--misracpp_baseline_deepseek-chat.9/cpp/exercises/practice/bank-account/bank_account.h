#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {
class Bankaccount {
public:
    Bankaccount();
    void open();
    void close();
    int balance() const;
    void deposit(int amount);
    void withdraw(int amount);
    
private:
    int m_balance;
    bool m_is_open;
    mutable std::mutex m_mutex;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {
class Bankaccount {
public:
    Bankaccount();
    void open();
    void deposit(int amount);
    void withdraw(int amount);
    void close();
    int balance() const;
    
private:
    mutable std::mutex mtx;
    int m_balance;
    bool m_is_open;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

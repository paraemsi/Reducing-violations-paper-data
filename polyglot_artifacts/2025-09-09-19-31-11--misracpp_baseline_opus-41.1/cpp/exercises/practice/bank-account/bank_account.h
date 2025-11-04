#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {
class Bankaccount {
public:
    Bankaccount();
    ~Bankaccount();
    
    void open();
    void close();
    int balance() const;
    void deposit(int amount);
    void withdraw(int amount);

private:
    mutable std::mutex account_mutex;
    int account_balance;
    bool is_open;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

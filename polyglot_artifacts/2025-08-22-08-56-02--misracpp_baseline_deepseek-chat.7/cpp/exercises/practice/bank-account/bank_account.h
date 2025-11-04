#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {
class Bankaccount {
public:
    void open();
    void close();
    void deposit(int amount);
    void withdraw(int amount);
    int balance() const;
    
    // Prevent copying
    Bankaccount() = default;
    Bankaccount(const Bankaccount&) = delete;
    Bankaccount& operator=(const Bankaccount&) = delete;
    
private:
    mutable std::mutex mtx;
    int account_balance = 0;
    bool is_open = false;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

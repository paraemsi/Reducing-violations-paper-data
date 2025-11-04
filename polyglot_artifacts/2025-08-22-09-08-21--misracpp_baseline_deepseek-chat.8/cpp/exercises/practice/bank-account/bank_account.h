#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {
class Bankaccount {
private:
    int balance_;
    bool is_open_;
    mutable std::mutex mtx_;
    
public:
    Bankaccount();
    void open();
    void close();
    int balance() const;
    void deposit(int amount);
    void withdraw(int amount);
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

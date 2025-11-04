#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {
class Bankaccount {
private:
    int balance_;
    bool is_open_;
    mutable std::mutex mutex_;
    
public:
    Bankaccount();
    // Prevent copying and moving
    Bankaccount(const Bankaccount&) = delete;
    Bankaccount& operator=(const Bankaccount&) = delete;
    Bankaccount(Bankaccount&&) = delete;
    Bankaccount& operator=(Bankaccount&&) = delete;
    
    void open();
    void close();
    int balance() const;
    void deposit(int amount);
    void withdraw(int amount);
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

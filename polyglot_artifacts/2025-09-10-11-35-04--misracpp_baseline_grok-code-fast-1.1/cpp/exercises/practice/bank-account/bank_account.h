#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {
class Bankaccount {
public:
    Bankaccount();
    void open();
    void close();
    void deposit(double amount);
    void withdraw(double amount);
    double balance() const;

private:
    double balance_;
    bool is_open_;
    mutable std::mutex mutex_;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

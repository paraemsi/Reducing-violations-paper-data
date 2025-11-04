#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {

// Forward declaration
class BankaccountImpl;

class Bankaccount {
public:
    Bankaccount();
    ~Bankaccount();
    void open();
    void deposit(int64_t amount);
    void withdraw(int64_t amount);
    int64_t balance() const;
    void close();
private:
    BankaccountImpl* impl;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

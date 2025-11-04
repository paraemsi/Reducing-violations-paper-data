#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <shared_mutex>

namespace Bankaccount {
class Bankaccount {
public:
    Bankaccount();
    void open();
    void close();
    void deposit(long amount);
    void withdraw(long amount);
    long balance() const;

private:
    long balance_;
    bool open_;
    mutable std::shared_mutex mutex_;
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

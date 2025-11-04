#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {

class Bankaccount {  // class Bankaccount
public:
    Bankaccount() = default;
    ~Bankaccount() = default;
    Bankaccount(const Bankaccount&) = delete;
    Bankaccount& operator=(const Bankaccount&) = delete;
    Bankaccount(Bankaccount&&) = delete;
    Bankaccount& operator=(Bankaccount&&) = delete;

    void open();
    void close();
    void deposit(int amount);
    void withdraw(int amount);
    int balance() const;

private:
    mutable std::mutex mutex_;
    bool is_open_ = false;
    int balance_ = 0;
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

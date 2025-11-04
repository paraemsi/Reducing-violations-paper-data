#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {

class Bankaccount {
public:
    ~Bankaccount() = default;
    Bankaccount() = default;
    Bankaccount(const Bankaccount&) = delete;
    Bankaccount& operator=(const Bankaccount&) = delete;
    Bankaccount(Bankaccount&&) = delete;
    Bankaccount& operator=(Bankaccount&&) = delete;

    void open();
    void close();
    void deposit(int amount);
    void withdraw(int amount);
    [[nodiscard]] int balance() const;

private:
    bool is_open_{false};
    bool is_closed_{false};
    int balance_{0};
    mutable std::mutex mutex_;
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

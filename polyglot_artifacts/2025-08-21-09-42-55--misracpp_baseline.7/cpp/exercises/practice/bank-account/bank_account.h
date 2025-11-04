#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <stdexcept>
#include <optional>

namespace Bankaccount {

class Bankaccount {
public:
    Bankaccount() : balance_(0), open_(false) {}

    void open() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (open_)
            throw std::runtime_error("Account already open");
        open_ = true;
        balance_ = 0;
    }

    void close() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!open_)
            throw std::runtime_error("Account already closed");
        open_ = false;
    }

    int balance() const {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!open_)
            throw std::runtime_error("Account closed");
        return balance_;
    }

    void deposit(int amount) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!open_)
            throw std::runtime_error("Account closed");
        if (amount < 0)
            throw std::runtime_error("Cannot deposit negative amount");
        balance_ += amount;
    }

    void withdraw(int amount) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!open_)
            throw std::runtime_error("Account closed");
        if (amount < 0)
            throw std::runtime_error("Cannot withdraw negative amount");
        if (amount > balance_)
            throw std::runtime_error("Insufficient funds");
        balance_ -= amount;
    }

private:
    mutable std::mutex mutex_;
    int balance_;
    bool open_;
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

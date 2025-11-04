#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (is_open_ || is_closed_) {
        throw std::runtime_error("Account already open");
    }
    is_open_ = true;
    balance_ = 0;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open_) {
        throw std::runtime_error("Account not open");
    }
    is_open_ = false;
    is_closed_ = true;
    balance_ = 0;
}

void Bankaccount::deposit(int amount) {
    if (amount < 0) {
        throw std::runtime_error("Cannot deposit negative amount");
    }
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open_) {
        throw std::runtime_error("Account not open");
    }
    balance_ += amount;
}

void Bankaccount::withdraw(int amount) {
    if (amount < 0) {
        throw std::runtime_error("Cannot withdraw negative amount");
    }
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open_) {
        throw std::runtime_error("Account not open");
    }
    if (balance_ < amount) {
        throw std::runtime_error("Insufficient funds");
    }
    balance_ -= amount;
}

int Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open_) {
        throw std::runtime_error("Account not open");
    }
    return balance_;
}

}  // namespace Bankaccount

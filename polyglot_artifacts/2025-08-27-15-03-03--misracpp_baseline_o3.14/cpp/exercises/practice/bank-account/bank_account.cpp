#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (is_open_) {
        throw std::runtime_error("Account already open");
    }
    is_open_ = true;
    balance_ = 0;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open_) {
        throw std::runtime_error("Account already closed");
    }
    is_open_ = false;
}

void Bankaccount::deposit(int amount) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    if (amount < 0) {
        throw std::domain_error("Cannot deposit negative amount");
    }
    balance_ += amount;
}

void Bankaccount::withdraw(int amount) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    if (amount < 0) {
        throw std::domain_error("Cannot withdraw negative amount");
    }
    if (amount > balance_) {
        throw std::domain_error("Insufficient funds");
    }
    balance_ -= amount;
}

int Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    return balance_;
}

}  // namespace Bankaccount

#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : balance_(static_cast<BalanceType>(0)), is_open_(false) {
}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (is_open_) {
        throw std::runtime_error("Account is already open");
    }
    is_open_ = true;
    balance_ = static_cast<BalanceType>(0);
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open_) {
        throw std::runtime_error("Account is not open");
    }
    is_open_ = false;
}

void Bankaccount::deposit(BalanceType amount) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    if (amount <= static_cast<BalanceType>(0)) {
        throw std::runtime_error("Deposit amount must be positive");
    }
    balance_ += amount;
}

void Bankaccount::withdraw(BalanceType amount) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    if (amount <= static_cast<BalanceType>(0)) {
        throw std::runtime_error("Withdrawal amount must be positive");
    }
    if (amount > balance_) {
        throw std::runtime_error("Insufficient funds");
    }
    balance_ -= amount;
}

BalanceType Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    return balance_;
}

}  // namespace Bankaccount

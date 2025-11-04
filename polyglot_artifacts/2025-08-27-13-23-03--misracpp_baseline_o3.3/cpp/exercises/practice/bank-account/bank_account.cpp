#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (open_) {
        throw std::runtime_error("Account already open");
    }
    balance_ = 0;
    open_ = true;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!open_) {
        throw std::runtime_error("Account not open");
    }
    balance_ = 0;
    open_ = false;
}

void Bankaccount::deposit(int amount) {
    if (amount < 0) {
        throw std::invalid_argument("Deposit amount must be non-negative");
    }
    std::lock_guard<std::mutex> lock(mtx_);
    if (!open_) {
        throw std::runtime_error("Account not open");
    }
    balance_ += amount;
}

void Bankaccount::withdraw(int amount) {
    if (amount < 0) {
        throw std::invalid_argument("Withdraw amount must be non-negative");
    }
    std::lock_guard<std::mutex> lock(mtx_);
    if (!open_) {
        throw std::runtime_error("Account not open");
    }
    if (amount > balance_) {
        throw std::runtime_error("Insufficient funds");
    }
    balance_ -= amount;
}

int Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!open_) {
        throw std::runtime_error("Account not open");
    }
    return balance_;
}

}  // namespace Bankaccount

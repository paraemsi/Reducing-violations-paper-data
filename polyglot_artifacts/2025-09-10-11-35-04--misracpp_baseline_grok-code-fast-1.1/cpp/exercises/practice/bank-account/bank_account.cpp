#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : balance_(0.0), is_open_(false) {}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (is_open_) {
        throw std::runtime_error("Account is already open");
    }
    balance_ = 0.0;
    is_open_ = true;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open_) {
        throw std::runtime_error("Account is already closed");
    }
    is_open_ = false;
}

void Bankaccount::deposit(double amount) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    if (amount < 0) {
        throw std::runtime_error("Deposit amount must be positive");
    }
    balance_ += amount;
}

void Bankaccount::withdraw(double amount) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    if (amount < 0) {
        throw std::runtime_error("Withdraw amount must be positive");
    }
    if (balance_ < amount) {
        throw std::runtime_error("Insufficient funds");
    }
    balance_ -= amount;
}

double Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    return balance_;
}

}  // namespace Bankaccount

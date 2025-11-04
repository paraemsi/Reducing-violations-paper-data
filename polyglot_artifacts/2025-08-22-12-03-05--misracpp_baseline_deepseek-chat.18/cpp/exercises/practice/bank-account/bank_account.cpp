#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : balance_(0), is_open_(false) {}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (is_open_) {
        throw std::runtime_error("Account is already open");
    }
    is_open_ = true;
    balance_ = 0;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open_) {
        throw std::runtime_error("Account is not open");
    }
    is_open_ = false;
}

int Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    return balance_;
}

void Bankaccount::deposit(int amount) {
    if (amount <= 0) {
        throw std::runtime_error("Deposit amount must be positive");
    }
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    balance_ += amount;
}

void Bankaccount::withdraw(int amount) {
    if (amount <= 0) {
        throw std::runtime_error("Withdrawal amount must be positive");
    }
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    if (amount > balance_) {
        throw std::runtime_error("Insufficient funds");
    }
    balance_ -= amount;
}

}

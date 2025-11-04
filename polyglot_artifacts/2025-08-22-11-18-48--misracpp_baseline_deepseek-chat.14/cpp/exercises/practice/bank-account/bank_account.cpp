#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : balance_(0), is_open_(false) {}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (is_open_) {
        throw std::runtime_error("Account already open");
    }
    is_open_ = true;
    balance_ = 0;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("Account not open");
    }
    is_open_ = false;
}

int Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("Account closed");
    }
    return balance_;
}

void Bankaccount::deposit(int amount) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("Account closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Invalid deposit amount");
    }
    balance_ += amount;
}

void Bankaccount::withdraw(int amount) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("Account closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Invalid withdrawal amount");
    }
    if (amount > balance_) {
        throw std::runtime_error("Insufficient funds");
    }
    balance_ -= amount;
}

}  // namespace Bankaccount

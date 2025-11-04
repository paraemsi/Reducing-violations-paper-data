#include "bank_account.h"

#include <mutex>
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : is_open_(false), balance_(0) {}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (is_open_) {
        throw std::runtime_error("account already open");
    }
    is_open_ = true;
    balance_ = 0;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("account not open");
    }
    is_open_ = false;
}

void Bankaccount::deposit(int amount) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("account not open");
    }
    if (amount <= 0) {
        throw std::runtime_error("deposit amount must be positive");
    }
    balance_ += amount;
}

void Bankaccount::withdraw(int amount) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("account not open");
    }
    if (amount <= 0) {
        throw std::runtime_error("withdrawal amount must be positive");
    }
    if (amount > balance_) {
        throw std::runtime_error("insufficient funds");
    }
    balance_ -= amount;
}

int Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("account not open");
    }
    return balance_;
}

}  // namespace Bankaccount

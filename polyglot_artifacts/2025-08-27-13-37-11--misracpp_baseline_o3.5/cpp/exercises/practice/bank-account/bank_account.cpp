#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (is_open_) {
        throw std::runtime_error("account already open");
    }
    balance_ = 0;
    is_open_ = true;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("account not open");
    }
    is_open_ = false;
    balance_ = 0;
}

void Bankaccount::deposit(int amount) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("account not open");
    }
    if (amount < 0) {
        throw std::invalid_argument("deposit amount must be non-negative");
    }
    balance_ += amount;
}

void Bankaccount::withdraw(int amount) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("account not open");
    }
    if (amount < 0) {
        throw std::invalid_argument("withdraw amount must be non-negative");
    }
    if (balance_ < amount) {
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

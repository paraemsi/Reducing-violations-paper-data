#include "bank_account.h"

namespace Bankaccount {

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (is_open_) {
        throw std::runtime_error("Account already open");
    }
    balance_ = 0;
    is_open_ = true;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("Account already closed");
    }
    is_open_ = false;
}

void Bankaccount::deposit(int amount) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    if (amount < 0) {
        throw std::runtime_error("Cannot deposit a negative amount");
    }
    balance_ += amount;
}

void Bankaccount::withdraw(int amount) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    if (amount < 0) {
        throw std::runtime_error("Cannot withdraw a negative amount");
    }
    if (amount > balance_) {
        throw std::runtime_error("Insufficient funds");
    }
    balance_ -= amount;
}

int Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    return balance_;
}

}  // namespace Bankaccount

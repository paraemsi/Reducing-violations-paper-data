#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mtx);
    if (is_open_) {
        throw std::runtime_error("Account is already open");
    }
    is_open_ = true;
    balance_ = 0;
}

void Bankaccount::deposit(std::int64_t amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Deposit amount must be positive");
    }
    balance_ += amount;
}

void Bankaccount::withdraw(std::int64_t amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Withdrawal amount must be positive");
    }
    if (amount > balance_) {
        throw std::runtime_error("Insufficient funds");
    }
    balance_ -= amount;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open_) {
        throw std::runtime_error("Account is not open");
    }
    is_open_ = false;
}

std::int64_t Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    return balance_;
}

}  // namespace Bankaccount

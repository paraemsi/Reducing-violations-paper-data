#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : balance_(0), is_open(false) {}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mtx);
    if (is_open) {
        throw std::runtime_error("Account is already open");
    }
    is_open = true;
    balance_ = 0;
}

void Bankaccount::deposit(std::int64_t amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account is closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Cannot deposit or withdraw negative amount");
    }
    balance_ += amount;
}

void Bankaccount::withdraw(std::int64_t amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account is closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Cannot deposit or withdraw negative amount");
    }
    if (amount > balance_) {
        throw std::runtime_error("Insufficient funds");
    }
    balance_ -= amount;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account is not open");
    }
    is_open = false;
}

std::int64_t Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account is closed");
    }
    return balance_;
}

}  // namespace Bankaccount

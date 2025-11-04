#include "bank_account.h"
#include <limits>
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : balance_{0}, open_{false} {
}

void Bankaccount::open() {
    std::lock_guard<std::shared_mutex> guard(mutex_);
    if (open_) {
        throw std::runtime_error("account already open");
    }
    open_ = true;
}

void Bankaccount::close() {
    std::lock_guard<std::shared_mutex> guard(mutex_);
    open_ = false;
}

void Bankaccount::deposit(long amount) {
    std::lock_guard<std::shared_mutex> guard(mutex_);
    if (!open_) {
        throw std::runtime_error("account is closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("deposit amount must be positive");
    }
    if (balance_ > std::numeric_limits<long>::max() - amount) {
        throw std::runtime_error("deposit would cause overflow");
    }
    balance_ += amount;
}

void Bankaccount::withdraw(long amount) {
    std::lock_guard<std::shared_mutex> guard(mutex_);
    if (!open_) {
        throw std::runtime_error("account is closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("withdraw amount must be positive");
    }
    if (balance_ < amount) {
        throw std::runtime_error("insufficient funds");
    }
    balance_ -= amount;
}

long Bankaccount::balance() const {
    std::shared_lock<std::shared_mutex> guard(mutex_);
    if (!open_) {
        throw std::runtime_error("account is closed");
    }
    return balance_;
}

}  // namespace Bankaccount

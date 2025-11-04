#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : balance_(0), is_open_(false) {}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mutex_);
    if ((is_open_)) {
        throw std::runtime_error("Account is already open");
    }
    is_open_ = true;
    balance_ = 0;
}

void Bankaccount::deposit(AccountValue amount) {
    if ((amount <= 0)) {
        throw std::invalid_argument("Deposit amount must be positive");
    }
    
    std::lock_guard<std::mutex> lock(mutex_);
    if (!(is_open_)) {
        throw std::runtime_error("Account is closed");
    }
    balance_ += amount;
}

void Bankaccount::withdraw(AccountValue amount) {
    if ((amount <= 0)) {
        throw std::invalid_argument("Withdrawal amount must be positive");
    }
    
    std::lock_guard<std::mutex> lock(mutex_);
    if (!(is_open_)) {
        throw std::runtime_error("Account is closed");
    }
    if ((amount > balance_)) {
        throw std::runtime_error("Insufficient funds");
    }
    balance_ -= amount;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mutex_);
    is_open_ = false;
}

AccountValue Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!(is_open_)) {
        throw std::runtime_error("Account is closed");
    }
    return balance_;
}

}  // namespace Bankaccount

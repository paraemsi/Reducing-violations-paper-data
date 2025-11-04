#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mtx);
    if (is_open) {
        throw std::runtime_error("Account is already open");
    } else {
        is_open = true;
        current_balance = 0;
    }
}

void Bankaccount::deposit(amount_t amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account is closed");
    } else {
        if (amount <= 0) {
            throw std::runtime_error("Deposit amount must be positive");
        } else {
            current_balance += amount;
        }
    }
}

void Bankaccount::withdraw(amount_t amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account is closed");
    } else {
        if (amount <= 0) {
            throw std::runtime_error("Withdrawal amount must be positive");
        } else {
            if (amount > current_balance) {
                throw std::runtime_error("Insufficient funds");
            } else {
                current_balance -= amount;
            }
        }
    }
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account is not open");
    } else {
        is_open = false;
        current_balance = 0;
    }
}

amount_t Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account is closed");
    } else {
        return current_balance;
    }
}

}  // namespace Bankaccount

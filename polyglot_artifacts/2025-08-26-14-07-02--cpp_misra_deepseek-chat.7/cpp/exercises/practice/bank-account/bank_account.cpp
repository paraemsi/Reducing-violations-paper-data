#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : current_balance(0), is_open(false) {
}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mtx);
    if (is_open) {
        throw std::runtime_error("Account is already open");
    }
    is_open = true;
    current_balance = 0;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account is not open");
    }
    is_open = false;
}

void Bankaccount::deposit(amount_t amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account is closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Deposit amount must be positive");
    }
    current_balance += amount;
}

void Bankaccount::withdraw(amount_t amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account is closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Withdrawal amount must be positive");
    }
    if (amount > current_balance) {
        throw std::runtime_error("Insufficient funds");
    }
    current_balance -= amount;
}

amount_t Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account is closed");
    }
    return current_balance;
}

}  // namespace Bankaccount

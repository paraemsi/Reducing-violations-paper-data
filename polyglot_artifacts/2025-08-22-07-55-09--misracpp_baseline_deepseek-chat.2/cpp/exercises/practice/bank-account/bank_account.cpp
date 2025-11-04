#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : current_balance(0), is_active(false) {
}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mtx);
    if (is_active) {
        throw std::runtime_error("Account is already open");
    }
    is_active = true;
    current_balance = 0;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_active) {
        throw std::runtime_error("Account is not open");
    }
    is_active = false;
}

int Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_active) {
        throw std::runtime_error("Account is closed");
    }
    return current_balance;
}

void Bankaccount::deposit(int amount) {
    if (amount <= 0) {
        throw std::runtime_error("Deposit amount must be positive");
    }
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_active) {
        throw std::runtime_error("Account is closed");
    }
    current_balance += amount;
}

void Bankaccount::withdraw(int amount) {
    if (amount <= 0) {
        throw std::runtime_error("Withdrawal amount must be positive");
    }
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_active) {
        throw std::runtime_error("Account is closed");
    }
    if (amount > current_balance) {
        throw std::runtime_error("Insufficient funds");
    }
    current_balance -= amount;
}

}  // namespace Bankaccount

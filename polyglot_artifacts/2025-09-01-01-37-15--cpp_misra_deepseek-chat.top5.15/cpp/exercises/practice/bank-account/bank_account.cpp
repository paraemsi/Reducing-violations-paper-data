#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : is_open(false), current_balance(0) {
}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mtx);
    if (is_open) {
        throw std::runtime_error("Account is already open");
    } else {
        // Empty else with braces
    }
    is_open = true;
    current_balance = 0;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account is not open");
    } else {
        // Empty else with braces
    }
    is_open = false;
}

void Bankaccount::deposit(std::int64_t amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account is closed");
    } else {
        // Empty else with braces
    }
    if (amount <= 0) {
        throw std::runtime_error("Deposit amount must be positive");
    } else {
        // Empty else with braces
    }
    current_balance += amount;
}

void Bankaccount::withdraw(std::int64_t amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account is closed");
    } else {
        // Empty else with braces
    }
    if (amount <= 0) {
        throw std::runtime_error("Withdrawal amount must be positive");
    } else {
        // Empty else with braces
    }
    if (amount > current_balance) {
        throw std::runtime_error("Insufficient funds");
    } else {
        // Empty else with braces
    }
    current_balance -= amount;
}

std::int64_t Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account is closed");
    } else {
        // Empty else with braces
    }
    return current_balance;
}

}  // namespace Bankaccount

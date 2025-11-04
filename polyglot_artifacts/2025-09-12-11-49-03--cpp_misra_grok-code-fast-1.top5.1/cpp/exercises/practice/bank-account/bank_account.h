#include <cstdint>
#include <mutex>
#include <stdexcept>

#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

namespace Bankaccount {
class Bankaccount {
private:
    std::mutex mtx;
    bool is_open;
    std::int64_t balance;

public:
    Bankaccount();
    bool open();
    bool close();
    bool deposit(std::int64_t amount);
    bool withdraw(std::int64_t amount);
    std::int64_t balance();
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

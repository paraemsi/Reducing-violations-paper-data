#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <cstdint>

namespace Bankaccount {
class Bankaccount {
private:
    std::int64_t balance_;
    bool is_open_;
    mutable std::mutex mutex_;
    
public:
    Bankaccount();
    void open();
    void close();
    void deposit(std::int64_t amount);
    void withdraw(std::int64_t amount);
    std::int64_t balance() const;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H

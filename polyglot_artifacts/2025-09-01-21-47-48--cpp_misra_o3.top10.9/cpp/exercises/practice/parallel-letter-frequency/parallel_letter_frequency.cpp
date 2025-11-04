#include "parallel_letter_frequency.h"

#include <thread>
#include <unordered_map>
#include <locale>
#include <string_view>

namespace parallel_letter_frequency {

letter_frequency_map frequency(const std::vector<std::string_view>& texts)
{
    const std::size_t totalTexts{texts.size()};

    if(totalTexts == 0U)
    {
        return {};
    }

    const std::size_t hardwareThreads{
        static_cast<std::size_t>(std::thread::hardware_concurrency())};
    const std::size_t numThreads{
        ((totalTexts < hardwareThreads) || (hardwareThreads == 0U))
            ? totalTexts
            : hardwareThreads};

    std::vector<std::unordered_map<char, std::uint32_t>> localResults(numThreads);

    std::vector<std::thread> workers;
    workers.reserve(numThreads);

    const std::locale loc{std::locale::classic()};

    auto worker =
        [&texts, &localResults, loc](std::size_t index,
                                    std::size_t start,
                                    std::size_t end) -> void
    {
        auto& localMap{localResults[index]};

        for(std::size_t i{start}; i < end; ++i)
        {
            for(char ch : texts[i])
            {
                /* Promote to unsigned-char to avoid undefined behaviour and
                 * to comply with MISRA rules regarding character values.   */
                const unsigned char uch{
                    static_cast<unsigned char>(ch)};

                if((std::isalpha(static_cast<char>(uch), loc)) != 0)
                {
                    const char lower{
                        static_cast<char>(std::tolower(
                            static_cast<char>(uch), loc))};
                    ++localMap[lower];
                }
            }
        }
    };

    const std::size_t blockSize{totalTexts / numThreads};
    std::size_t       blockStart{0U};

    for(std::size_t t{0U}; t < numThreads; ++t)
    {
        const std::size_t blockEnd{
            (t == (numThreads - 1U)) ? totalTexts : (blockStart + blockSize)};
        workers.emplace_back(worker, t, blockStart, blockEnd);
        blockStart = blockEnd;
    }

    for(auto& th : workers)
    {
        if(th.joinable())
        {
            th.join();
        }
    }

    letter_frequency_map result{};

    for(const auto& localMap : localResults)
    {
        for(const auto& keyValue : localMap)
        {
            result[keyValue.first] += keyValue.second;
        }
    }

    return result;
}

}  // namespace parallel_letter_frequency

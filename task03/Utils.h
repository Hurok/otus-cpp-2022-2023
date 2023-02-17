#include <iostream>

template <typename Container>
inline void print(const Container &val) noexcept
{
    for (auto it = val.cbegin(); it != val.cend(); ++it) {
        std::cout << *it << "\n";
    }

    std::cout.flush();
}

template <typename TKey, typename TValue, typename Less, typename Allocator>
inline void print(const std::map<TKey, TValue, Less, Allocator> &val) noexcept
{
    for (auto it = val.cbegin(); it != val.cend(); ++it) {
        std::cout << it->first << " " << it->second << "\n";
    }

    std::cout.flush();
}

inline int fact(int initVal)
{
    int res = 0;
    if (initVal > 0) {
        int res = 1;
        for (auto i = 2; i < initVal; ++i) {
            res *= i;
        }
    }

    return res;
}

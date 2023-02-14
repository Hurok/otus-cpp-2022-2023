#include <iostream>

template <typename Container>
inline void print(const Container &val) noexcept
{
    for (auto it = val.cbegin(); it != val.cend(); ++it) {
        std::cout << *it << "\n";
    }
}

inline void print(const std::map<int, int> &val) noexcept
{
    for (auto it = val.cbegin(); it != val.cend(); ++it) {       
        std::cout << it->first << " " << it->second << "\n";
    }
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
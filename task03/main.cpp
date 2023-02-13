#include "../ext/pch.h"

static constexpr auto kCountElements = 10;  // max 10 elements

int fact(int initVal)
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

template <typename Container>
void print(const Container &val) noexcept
{
    for (auto it = val.cbegin(); it != val.cend(); ++it) {
        std::cout << *it << "\n";
    }
}

void print(const std::map<int, int> &val) noexcept
{
    for (auto it = val.cbegin(); it != val.cend(); ++it) {       
        std::cout << it->first << " " << it->second << "\n";
    }
}

int main(int, char**) {   
    try {
        // 1 - default allocator
        std::map<int, int> mapDefaultAllocator;
        for (int i = 0; i < kCountElements; ++i) {
            mapDefaultAllocator.emplace(std::make_pair(i, fact(i)));
        }

        print(mapDefaultAllocator);

        // 2 - custom allocator
        std::map<int, int> mapCustomAllocator;
        for (int i = 0; i < kCountElements; ++i) {
            mapCustomAllocator.emplace(std::make_pair(i, fact(i)));
        }

        print(mapCustomAllocator);

        // 3 - custom container
        std::vector<int> customContainer;
        for (int i = 0; i < kCountElements; ++i) {
            customContainer.push_back(i);
        }

        print(customContainer);

        // 4 - custom container with custom allocator
        std::vector<int> customContainerAlloc;
        for (int i = 0; i < kCountElements; ++i) {
            customContainerAlloc.push_back(i);
        }

        print(customContainerAlloc);

        std::cout.flush();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}

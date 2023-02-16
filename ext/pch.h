#ifndef PHCHELPER_H
#define PHCHELPER_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <list>
#include <numeric>
#include <map>
#include <set>
#include <optional>

#if defined (_WIN32)
#include <Windows.h>
#elif defined (__linux__) // _WIN32
#include <unistd.h>
#endif // __linux__

inline std::string &ltrim(std::string &inOut) noexcept {
    auto itRemove = std::find_if(inOut.begin(), inOut.end(), [](const char ch) -> bool {
        return !std::isspace(static_cast<int>(ch));
    });

    if (itRemove != inOut.end())
        inOut.erase(inOut.begin(), itRemove);

    return inOut;
}

inline std::string &rtrim(std::string &inOut) noexcept {
    auto itRemove = std::find_if(inOut.rbegin(), inOut.rend(), [](const char ch) -> bool {
        return !std::isspace(static_cast<int>(ch));
    }).base();

    if (itRemove != inOut.end())
        inOut.erase(itRemove, inOut.end());

    return inOut;
}

inline std::string &trim(std::string &inOut) noexcept {
    ltrim(inOut);
    rtrim(inOut);

    return inOut;
}

#ifdef _MSC_VER 
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

#endif // !PHCHELPER_H

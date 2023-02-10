#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <array>

struct SIpV4
{
    std::array<uint8_t, 4> ip;

    static bool comparer(const SIpV4 &l, const SIpV4 &r) noexcept;
    static SIpV4 fromString(const std::string &val);
    friend std::ostream &operator << (std::ostream &stream, const SIpV4 &other) noexcept;
};

#endif // !STRUCTURES_H
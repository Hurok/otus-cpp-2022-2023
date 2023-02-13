#include "../ext/pch.h"
#include "Structures.h"

static constexpr auto kTabsInLine = 2;

void normalizeLine(std::string &inOut)
{
    auto itRemove = std::remove_if(inOut.begin(), inOut.end(), [](const char ch) -> bool {
        return ch == '\r';        
    });

    if (itRemove != inOut.end())
        inOut.erase(itRemove, inOut.end());    

    if (!inOut.empty() && inOut.back() != '\n')
        throw std::logic_error("invalid line terminator, expected '\\n' or '\\r\\n'");

    const auto countTab = std::accumulate(inOut.cbegin(), inOut.cend(), 0, [](int res, const char ch) -> int {
        return ch == '\t' ? ++res : res;
    });

    if (countTab != kTabsInLine) {
        std::stringstream ss;
        ss << "invalid \\t count, expected " << kTabsInLine << ", line exists " << countTab;
        throw std::logic_error(ss.str());
    }        
}

std::string getIpStr(const std::string &line) {
    std::string ip;
    

    return ip;
}

int main(int, char**) {   
    try {
        std::vector<std::string> lines = {
            "1.1.1.1\ttext2\ttext3\n", 
            "46.70.70.1\ttext2\ttext3\r\n", 
            "1.46.3.1\ttext2\ttext3\n",
            "1.2.70.1\ttext2\ttext3\n",
            "46.3.10.1\ttext2\ttext3\n"
        };

        std::vector<SIpV4> listIpV4;
        for (auto &i : lines) {
            normalizeLine(i);

            auto it = std::find_if(i.cbegin(), i.cend(), [](const char ch) -> bool {
                return ch == '\t';
            });

            if (it == i.cend())
                throw std::logic_error("not found ip address in line");

            auto ipv4 = SIpV4::fromString(std::string(i.cbegin(), it));
            listIpV4.push_back(ipv4);
        }

        // out result
        std::sort(listIpV4.begin(), listIpV4.end(), SIpV4::comparer);
        std::stringstream ssIp1;            // temp for result
        std::stringstream ssIp46_70;        // temp for result
        std::stringstream ssIp46Any;        // temp for result

        const int sz = listIpV4.size();
        for (int i = 0; i < sz; ++i) {
            const auto &ip = listIpV4.at(i);

            if (ip.oct1() == 1)
                ssIp1 << ip << "\n";

            if (ip.oct1() == 46 && ip.oct2() == 70)
                ssIp46_70 << ip << "\n";

            if (ip.oct1() == 46 || ip.oct2() == 46 || ip.oct3() == 46 || ip.oct4() == 46)
                ssIp46Any << ip << "\n";

            std::cout << ip << std::endl;
        }
        
        auto ssIp1Str = ssIp1.str();
        auto ssIp46_70Str = ssIp46_70.str();
        auto ssIp46AnyStr = ssIp46Any.str();

        std::cout   << rtrim(ssIp1Str) << "\n"
                    << rtrim(ssIp46_70Str) << "\n"
                    << rtrim(ssIp46AnyStr) << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}

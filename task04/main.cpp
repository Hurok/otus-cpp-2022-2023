#include "../ext/pch.h"

int main(int, char**) {   
    try {
        throw std::logic_error("not implemented");
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}

#include "../ext/pch.h"

int main(int, char**) {   
    try {
        
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}

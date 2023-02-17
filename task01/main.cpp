#include "../ext/pch.h"

int main (int argc, char **argv)
{
    UNUSED(argc);
    UNUSED(argv);

    // если оставить замену N, как по условию, то не очень хорошо, потому что N не похоже на шаблон
    // а вот {BUILD_NUMBER} уже лучше похоже
    std::cout << "build {BUILD_NUMBER}\n"
                 "Hello, World!" << std::endl;

    return EXIT_SUCCESS;
}

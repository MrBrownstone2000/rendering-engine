#include "testCore/runner.hpp"

#include <iostream>

int main()
{
    std::cout << "Running tests..." << std::endl;
    test::TestAll();
    return 0;
}

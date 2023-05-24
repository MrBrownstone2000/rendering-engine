#include "testIOC.hpp"
#include "testSingleton.hpp"
#include <iostream>

int main()
{
    {
        TestIOC test{ };
        if (test.init())
            test.run();
        else
            std::cerr << "Error: test failed to initialized..." << std::endl;
        test.shutdown();
    }

    {
        TestSingleton test{ };
        if (test.init())
            test.run();
        else
            std::cerr << "Error: test failed to initialized..." << std::endl;
        test.shutdown();
    }
    
    return 0;
}

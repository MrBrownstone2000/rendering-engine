#include "testCore/test.hpp"

#include <iostream>

class Cat : public TestBase, RegisteredInFactory<Cat>
{
public:
    Cat()
    {
        FACTORY_INIT;
        std::cout << "Constructing Cat..." << std::endl;
    }
    
    ~Cat() { }

    static TestBase* CreateInstance()
    {
        return new Cat();
    }
    
    void Run() override
    {
        std::cout << "Testing Cat..." << std::endl;
    }
};


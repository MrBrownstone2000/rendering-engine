#include "testCore/factory.hpp"
#include "testCore/testBase.hpp"

#include <iostream>


#define TEST(_TEST_NAME_)                                                   \
void test_##_TEST_NAME_();                                                  \
class _TEST_NAME_ : public TestBase, RegisteredInFactory<_TEST_NAME_>       \
{                                                                           \
public:                                                                     \
    _TEST_NAME_()                                                           \
    {                                                                       \
        FACTORY_INIT;                                                       \
    }                                                                       \
                                                                            \
    static TestBase* CreateInstance()                                       \
    {                                                                       \
        return new _TEST_NAME_();                                           \
    }                                                                       \
                                                                            \
    void Run() override                                                     \
    {                                                                       \
        std::cout << "Running " << #_TEST_NAME_ << std::endl;               \
        test_##_TEST_NAME_();                                               \
    }                                                                       \
};                                                                          \
                                                                            \
void test_##_TEST_NAME_()                                                   \


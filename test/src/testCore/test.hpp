#ifndef __TEST_HPP__
#define __TEST_HPP__

#include "testCore/factory.hpp"
#include "testCore/base.hpp"

#include <iostream>
#include <string>

#define TEST_MODULE(_MODULE_NAME_)                                          \
namespace { const char _TEST_MODULE_[] = #_MODULE_NAME_; }                 \
namespace                                                                   \


#define TEST(_TEST_NAME_)                                                   \
void test_##_TEST_NAME_();                                                  \
class _TEST_NAME_ : public test::TestBase, test::RegisteredInFactory<_TEST_MODULE_, _TEST_NAME_>       \
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
        std::cout << "From module " << _TEST_MODULE_ << std::endl;               \
        test_##_TEST_NAME_();                                               \
    }                                                                       \
};                                                                          \
                                                                            \
void test_##_TEST_NAME_()                                                   \


#endif

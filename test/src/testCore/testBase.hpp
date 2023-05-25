#ifndef __TESTBASE_HPP__
#define __TESTBASE_HPP__

class TestBase
{
protected:
	TestBase() = default;
public:
    virtual ~TestBase() = default;
    virtual void Run() = 0;
};

#endif

